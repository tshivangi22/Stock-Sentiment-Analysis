import glob
import subprocess

for f in glob.glob("*.ipynb"):
    print("Cleaning metadata (keeping outputs):", f)
    subprocess.run([
        "python", "-m", "nbstripout",
        "--keep-output",
        "--extra-keys", "metadata.widgets",
        f
    ])
