def ordinalSuffix(num: int) -> str:
    end = num % 100
    if end < 10 or end > 20:
        match end % 10:
            case 1:
                return str(num) + "st"
            case 2:
                return str(num) + "nd"
            case 3:
                return str(num) + "rd"
    return str(num) + "th"