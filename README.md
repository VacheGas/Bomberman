# Bomberman

### Project Configuration steps

1. install necessary tools if needed
```bash
brew install cmake ninja clang-format
pip install cmake-format
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
