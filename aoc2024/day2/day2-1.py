def convertToInt(string):
    return list(map(int, string.split()))

def analyseReport(report):
    reportInt = convertToInt(report)
    increasing = True
    decreasing = True

    for i in range(1, len(reportInt)):
        diff = reportInt[i] - reportInt[i-1]

        if abs(diff) < 1 or abs(diff) > 3:
            return False

        if diff < 0:
            increasing = False
        if diff > 0:
            decreasing = False

    # at this point within the safe range
    return increasing or decreasing

def main():
    file_path = input("Enter file name: ")

    inputs = []
    with open (file_path, 'r') as file:
        for line in file:
            inputs.append(line)
    
    safeReportNum = 0
    for i in range (len(inputs)):
        if analyseReport(inputs[i]):
            safeReportNum += 1

    print(safeReportNum)

if __name__ == "__main__":
    main()

