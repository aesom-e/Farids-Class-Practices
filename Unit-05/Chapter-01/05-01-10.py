def getHoursMinutesSeconds(seconds: int) -> str:
    if not seconds:
        return "0s"

    times = [int(seconds / (3600*24)),
             int((seconds % (3600*24)) / 3600),
             int((seconds % 3600) / 60),
             int(seconds % 60)]
    suffixes = ['d', 'h', 'm', 's']
    ret = ""
    for i in range(len(times)):
        if times[i]:
            ret += ("" if not ret else " ") + str(times[i]) + suffixes[i]
    return ret