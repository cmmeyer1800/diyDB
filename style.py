import os
import subprocess

def main() -> None:
    baseDir = os.getcwd()
    os.chdir(os.path.join(baseDir, "src"))
    srcDir = os.getcwd()
    for dir in (f for f in os.listdir()):
        if dir.find(".") != -1:
            continue
        else:
            os.chdir(os.path.join(srcDir, dir))
            for file in (f for f in os.listdir()):
                if file.find(".") == -1:
                    continue
                else:
                    subprocess.run(["clang-format", "-style=google", "-i", file])

main()