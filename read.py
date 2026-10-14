searcher = input("what protocol or ip you wanna find ?: ")

with open("logs.txt", "r") as Log_File:
    content = Log_File.read()
    pos = content.find(searcher)
    if pos != -1:
        print(content[pos:pos+10])
    else:
        print(f"Failure to find {searcher}")

