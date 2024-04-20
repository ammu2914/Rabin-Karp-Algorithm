d = 10

def rabinKarp(pattern, input, p):
    m = len(pattern)
    n = len(input)
    hash_val = 1

    for _ in range(m - 1):
        hash_val = (hash_val * d) % p

    ph = 0
    th = 0

    # Calculate hash value for pattern and input
    for i in range(m):
        ph = (d * ph + ord(pattern[i])) % p
        th = (d * th + ord(input[i])) % p

    # Slide the pattern over text one by one
    for i in range(n - m + 1):
        # Check the hash values of current substring of input
        # and pattern. If the hash values match then only
        # check for characters one by one
        if ph == th:
            # Check for characters one by one
            for j in range(m):
                if input[i + j] != pattern[j]:
                    break
            else:
                print("Pattern is found at position:", i + 1)

        # Calculate hash value for next substring of input:
        # Remove leading digit, add trailing digit
        if i < n - m:
            th = (d * (th - ord(input[i]) * hash_val) + ord(input[i + m])) % p

            # We might get negative value of th, converting it to positive
            if th < 0:
                th += p


def main():
    try:
        with open('input3.txt', 'r') as file:
            input_string = file.readline().strip()
            pattern_string = file.readline().strip()
    except FileNotFoundError:
        print("Error: input file not found.")
        return

    p = 13
    rabinKarp(pattern_string, input_string, p)


if __name__ == "__main__":
    main()
