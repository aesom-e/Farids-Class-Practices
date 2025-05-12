def convertToCelsius(fahrenheight: float) -> float:
    return (fahrenheight - 32) * (5/9) # Inefficient, but I don't care (also we're using python)

def convertToFahrenheit(celsius: float) -> float:
    return celsius * (9/5) + 32