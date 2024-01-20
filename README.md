# Bomberman

### Project Configuration steps

1. install necessary tools if needed
```bash
brew install cmake ninja clang-format doxygen
```
2. Clone the repository
```bash
git clone https://github.com/VacheGas/Bomberman.git --recursive
```

3. Build files generation, we support Ninja
```bash
mkdir "BUILD_DIR"
cd "BUILD_DIR"
cmake .. -G Ninja
ninja
```

4. If you want to generate documentation, you need to execute these commands in the build folder.
```
ninja documentation
open html/index.html  
```