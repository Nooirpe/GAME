# Installation Guide for RunMo! on Windows

## Prerequisites

To run this game, you need:

- Windows operating system
- MinGW with g++ compiler (if you want to compile the game yourself)

## Option 1: Quick Run (Pre-compiled)

1. Extract all files from the ZIP archive to a folder on your computer
2. Make sure all SDL2 DLL files are in the same folder as the game executable
3. Double-click on `RunMo.exe` to launch the game

## Option 2: Build from Source

If you want to compile the game yourself, follow these steps:

1. Install MinGW with g++ compiler if you don't have it already

   - You can download it from [MinGW](https://www.mingw-w64.org/downloads/)
   - Make sure to add MinGW's bin directory to your system PATH

2. Extract all files from the ZIP archive to a folder

3. Open Command Prompt or PowerShell in the game folder and run:

   ```
   mingw32-make clean
   mingw32-make
   ```

4. Run the game by typing:
   ```
   .\RunMo
   ```

## Troubleshooting

- If you get "SDL2.dll not found" or similar errors, make sure all DLL files are in the same folder as the executable.
- If the game doesn't compile, check that MinGW is properly installed and in your PATH.

## File Structure

- `RunMo.exe`: The game executable
- `SDL2.dll`, `SDL2_image.dll`, `SDL2_mixer.dll`, `SDL2_ttf.dll`: Required SDL2 libraries
- `Assets/`: Contains all game assets (images, sounds, etc.)
- `src/`: Contains the SDL2 include files and libraries for building from source

## Controls

- Arrow keys: Move character
- Space: Jump
- ESC: Pause/Menu

Enjoy playing RunMo!

---

# Hướng dẫn Cài đặt RunMo! trên Windows

## Yêu cầu hệ thống

Để chạy trò chơi này, bạn cần:

- Hệ điều hành Windows
- MinGW với trình biên dịch g++ (nếu bạn muốn tự biên dịch trò chơi)

## Cách 1: Chạy Nhanh (Đã biên dịch sẵn)

1. Giải nén tất cả các tệp từ tập tin ZIP vào một thư mục trên máy tính của bạn
2. Đảm bảo tất cả các tệp DLL của SDL2 nằm trong cùng thư mục với tệp thực thi trò chơi
3. Nhấp đúp vào `RunMo.exe` để khởi động trò chơi

## Cách 2: Biên dịch từ Mã nguồn

Nếu bạn muốn tự biên dịch trò chơi, hãy làm theo các bước sau:

1. Cài đặt MinGW với trình biên dịch g++ nếu bạn chưa có

   - Bạn có thể tải xuống từ [MinGW](https://www.mingw-w64.org/downloads/)
   - Đảm bảo thêm thư mục bin của MinGW vào PATH của hệ thống

2. Giải nén tất cả các tệp từ tập tin ZIP vào một thư mục

3. Mở Command Prompt hoặc PowerShell trong thư mục trò chơi và chạy:

   ```
   mingw32-make clean
   mingw32-make
   ```

4. Chạy trò chơi bằng cách gõ:
   ```
   .\RunMo
   ```

## Xử lý sự cố

- Nếu bạn gặp lỗi "SDL2.dll not found" hoặc tương tự, hãy đảm bảo tất cả các tệp DLL nằm trong cùng thư mục với tệp thực thi.
- Nếu trò chơi không biên dịch được, hãy kiểm tra xem MinGW đã được cài đặt đúng cách và nằm trong PATH của bạn chưa.

## Cấu trúc tệp

- `RunMo.exe`: Tệp thực thi trò chơi
- `SDL2.dll`, `SDL2_image.dll`, `SDL2_mixer.dll`, `SDL2_ttf.dll`: Thư viện SDL2 cần thiết
- `Assets/`: Chứa tất cả tài nguyên trò chơi (hình ảnh, âm thanh, v.v.)
- `src/`: Chứa các tệp include và thư viện SDL2 để biên dịch từ mã nguồn

## Điều khiển

- Phím mũi tên: Di chuyển nhân vật
- Phím Space: Nhảy
- Phím ESC: Tạm dừng/Menu

Chúc bạn chơi game vui vẻ!
