import os
import subprocess

# Get the value of BOMBERMAN_DIR environment variable
BOMBERMAN_DIR = os.environ.get('BOMBERMAN_DIR')

test_dirs = [dirpath for dirpath, _, _ in os.walk('src') if dirpath.endswith('tests')]
test_result = 0
for dir in test_dirs:
    os.chdir(os.path.join(BOMBERMAN_DIR, 'build', dir))
    result = subprocess.run(['ctest', '-j32', '--verbose', '--output-junit', 'test_results.xml'])
    if result.returncode != 0:
        test_result = 1
os.chdir(BOMBERMAN_DIR)


exit(test_result)