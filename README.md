Для работы с json:

sudo apt install nlohmann-json3-dev



git clone https://github.com/LevDzhagupovMSU/scanner.git
cd scanner

mkdir build
cd build
cmake ..
make

./bin/task1



При запуске введите период сканирования в секундах.
Для остановки нажмите `q` и Enter.

Результат сохраняется в `~/.media_files`
