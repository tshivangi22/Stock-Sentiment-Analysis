import glob
import subprocess
import os

# find all notebooks in current folder
for f in glob.glob("*.ipynb"):
    print("Cleaning:", f)
    subprocess.run([
        "python", "-m", "nbstripout",
        "--extra-keys", "metadata.widgets",
        f
    ])
