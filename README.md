# Ftxui Application Audio Generator

## Audio Generator

- Ứng dụng đầu tiên dùng để tạo các tệp audio sinway và được vẽ thông qua ftxui.

## Riêng Cho Window

- Cần sử dụng và tải về [msys2](https://www.msys2.org/)
- Trong các tệp tại thư mục `C:\msys64`, sử dụng phần mềm __mingw64.exe__
- Sau đó tải về các tệp cấu hình phục thuộc sau (bắt buộc)

```cmake
pacman -S mingw-w64-ucrt-x86_64-gcc
pacman -S mingw-w64-ucrt-x86_64-cmake
# pacman -S mingw-w64-ucrt-x86_64-ncurses
```

> Chú thích: ncurses không có mặc định trên windows nên cần riêng.

## Build

Sử dụng lệnh sau để dựng ứng dụng

```cmake
cmake -S . -B out
cmake --build out
```