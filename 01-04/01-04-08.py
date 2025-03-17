def main() -> int | None:
    H = float(input())
    R = float(input())
    print(f"{2 * 3.14159 * R * H + 2 * 3.14159 * R ** 2}")

if __name__ == "__main__":
    exit(main())