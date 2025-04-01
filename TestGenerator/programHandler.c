#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#endif
#include "constants.h"
#include "error.h"
#include "programHandler.h"

char* programHandler_GetProgramName(char* programNumber) {
    int numbers[3];
    if(sscanf(programNumber, "%d-%d-%d", &(numbers[0]), &(numbers[1]), &(numbers[2])) != 3)
        error("Invalid program number: %s\n", programNumber);
    
    // Get the name of the program 
    char raw[MAX_PROGRAM_PATH_SIZE];
    if(!raw) error("Failed to create a buffer to store the program path\n");
    snprintf(raw, MAX_PROGRAM_PATH_SIZE,
             "C:/PyCharm/CompSci11/Classroom/Practices-E-Sadler_REAL/Practices-E-Sadler/tests/%02d-%02d-%02d/generator.py",
             numbers[0], numbers[1], numbers[2]);
    
    // Condense the memory used
    char* ret = calloc(strlen(raw)+1, 1);
    if(!ret) error("Failed to create a buffer to store the program path\n");
    strcpy(ret, raw);

    return ret;
}

#ifdef WIN32
char** programHandler_RunPythonProgram(char* path) {
    HANDLE hChildStdoutRd, hChildStdoutWr;
    HANDLE hChildStdinRd, hChildStdinWr;
    SECURITY_ATTRIBUTES saAttr;
    PROCESS_INFORMATION piProcInfo;
    STARTUPINFO siStartInfo;
    char** programIO = calloc(2, sizeof(char*));

    if (!programIO) error("Failed to allocate memory for program IO");
    programIO[0] = calloc(PROGRAMIO_INITIAL_SIZE, 1);
    programIO[1] = calloc(PROGRAMIO_INITIAL_SIZE, 1);
    if (!programIO[0] || !programIO[1]) error("Failed to allocate input/output buffer");

    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    // Create pipes for communication
    if (!CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &saAttr, 0))
        error("Stdout pipe creation failed");

    if (!CreatePipe(&hChildStdinRd, &hChildStdinWr, &saAttr, 0))
        error("Stdin pipe creation failed");

    // Ensure read handles are not inherited
    SetHandleInformation(hChildStdoutRd, HANDLE_FLAG_INHERIT, 0);

    // Set up process info
    ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
    siStartInfo.cb = sizeof(STARTUPINFO);
    siStartInfo.hStdError = hChildStdoutWr;
    siStartInfo.hStdOutput = hChildStdoutWr;
    siStartInfo.hStdInput = hChildStdinRd;
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

    // Command string
    char processName[MAX_PROGRAM_PATH_SIZE + 12];
    snprintf(processName, sizeof(processName), "python -u \"%s\"", path);

    // Create the child process
    if (!CreateProcess(NULL, processName, NULL, NULL, TRUE, 0, NULL, NULL, &siStartInfo, &piProcInfo)) {
        error("CreateProcess failed");
    }

    CloseHandle(hChildStdoutWr);
    CloseHandle(hChildStdinRd);

    // Writing input and checking output
    char inputBuffer[INPUT_BUFFER_SIZE];
    DWORD written;
    size_t inputSize = 0;

    while (1) {
        // Prompt user for input
        if (fgets(inputBuffer, INPUT_BUFFER_SIZE, stdin)) {
            size_t len = strlen(inputBuffer);

            // Store input dynamically
            if (inputSize + len >= PROGRAMIO_INITIAL_SIZE) {
                programIO[0] = realloc(programIO[0], inputSize + len + 1);
                if (!programIO[0]) error("Failed to reallocate input buffer");
            }

            strcat(programIO[0], inputBuffer);
            inputSize += len;

            // Write input to Python process
            WriteFile(hChildStdinWr, inputBuffer, len, &written, NULL);
        }

        // Check if Python has produced output
        DWORD availableBytes = 0;
        if (PeekNamedPipe(hChildStdoutRd, NULL, 0, NULL, &availableBytes, NULL) && availableBytes > 0) {
            break; // Python responded, stop input loop
        }
    }

    CloseHandle(hChildStdinWr);

    // Read output from Python
    DWORD bytesRead;
    char buffer[256];
    DWORD totalSize = 0;

    while (1) {
        DWORD availableBytes = 0;
        if (!PeekNamedPipe(hChildStdoutRd, NULL, 0, NULL, &availableBytes, NULL)) {
            break;  // Pipe closed
        }

        if (availableBytes > 0) {
            ReadFile(hChildStdoutRd, buffer, sizeof(buffer) - 1, &bytesRead, NULL);
            if (bytesRead > 0) {
                buffer[bytesRead] = '\0';

                // Store output dynamically
                if (totalSize + bytesRead >= PROGRAMIO_INITIAL_SIZE) {
                    programIO[1] = realloc(programIO[1], totalSize + bytesRead + 1);
                    if (!programIO[1]) error("Failed to reallocate output buffer");
                }

                strcat(programIO[1], buffer);
                totalSize += bytesRead;
            }
        } else {
            Sleep(100);
        }

        // Check if process has exited
        DWORD exitCode;
        if (!GetExitCodeProcess(piProcInfo.hProcess, &exitCode) || exitCode != STILL_ACTIVE) {
            break;
        }
    }

    CloseHandle(hChildStdoutRd);
    WaitForSingleObject(piProcInfo.hProcess, INFINITE);
    CloseHandle(piProcInfo.hProcess);
    CloseHandle(piProcInfo.hThread);

    return programIO;
}
#else
char** programHandler_RunPythonProgram(char* path) {
    int inPipe[2], outPipe[2];
    pid_t pid;
    char** programIO = calloc(2, sizeof(char*));

    if(!programIO) error("Failed to allocate memory for program IO");
    programIO[0] = calloc(PROGRAMIO_INITIAL_SIZE, 1);
    programIO[1] = calloc(PROGRAMIO_INITIAL_SIZE, 1);
    if(!programIO[0] || !programIO[1]) error("Failed to allocate input/output buffer");

    if(pipe(inPipe) == -1 || pipe(outPipe) == -1)
        error("Pipe creation failed");

    if((pid = fork()) == -1)
        error("Fork failed");

    if(!pid) {
        // Redirect stdio and stdout
        dup2(inPipe[0], STDIN_FILENO);
        dup2(outPipe[1], STDOUT_FILENO);
        close(inPipe[0]);
        close(inPipe[1]);
        close(outPipe[0]);
        close(outPipe[1]);

        execlp("python3", "python3", "-u", path, NULL);
        error("Failed to exec Python");
    } else {
        close(inPipe[0]);
        close(outPipe[1]);

        fcntl(outPipe[0], F_SETFL, O_NONBLOCK);

        // Handle IO
        char inputBuffer[INPUT_BUFFER_SIZE];
        int inputSize = 0;
        while(1) {
            if(fgets(inputBuffer, INPUT_BUFFER_SIZE, stdin)) {
                int len = strlen(inputBuffer);

                // Store input dynamically
                if(inputSize + len >= PROGRAMIO_INITIAL_SIZE) {
                    programIO[0] = realloc(programIO[0], inputSize + len + 1);
                    if(!programIO[0]) error("Failed to reallocate input buffer");
                }

                strcat(programIO[0], inputBuffer);
                inputSize += len;

                // Write input to Python process
                write(inPipe[1], inputBuffer, len);
            }

            // Check if Python has produced output
            usleep(50000);
            char buffer[256];
            int bytesRead = read(outPipe[0], buffer, sizeof(buffer) - 1);

            if(bytesRead > 0) {
                buffer[bytesRead] = 0;

                // Store output dynamically
                size_t totalSize = strlen(programIO[1]);
                programIO[1] = realloc(programIO[1], totalSize + bytesRead + 1);
                if (!programIO[1]) error("Failed to reallocate output buffer");

                strcat(programIO[1], buffer);
                break;
            }
        }
        close(inPipe[1]);

        // Read remaining output from Python
        char buffer[256];
        ssize_t bytesRead;
        while((bytesRead = read(outPipe[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytesRead] = 0;

            // Store output dynamically
            size_t totalSize = strlen(programIO[1]);
            programIO[1] = realloc(programIO[1], totalSize + bytesRead + 1);
            if (!programIO[1]) error("Failed to reallocate output buffer");

            strcat(programIO[1], buffer);
        }

        close(outPipe[0]);
        waitpid(pid, NULL, 0);
    }
    return programIO;
}
#endif