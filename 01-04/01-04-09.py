def main() -> int | None:
    Ra = float(input())
    Rb = float(input())
    H = float(input())
    print(f"{(1/3) * 3.14159 * H * (Ra ** 2 + Ra * Rb + Rb ** 2)}")

if __name__ == "__main__":
    exit(main())