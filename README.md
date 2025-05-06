# **RunMo!**

# **_English/Tiếng Anh_**

## **Introduction**

- Name: Nguyen Le Dung - K69I - UET
- Student ID: 24022633
- Game name: RunMo!

## **Description**

### **General Description**

- RunMo! is a game developed using C++ and SDL2, created as a project for the Advanced Programming class (2425II_INT2215_12)
- You play as a knight. All you need to do is overcome obstacles and reach the end
- The game concept is inspired by and simplified from "I Wanna Be the Guy: The Movie: The Game (Michael O'Reilly, 2007)"
- Video: [RunMo!](https://youtu.be/JKnO0Bbb6xU)

### **Details**

- An Intro section when first entering the game
- Main menu
- The game consists of 3 levels, with more features and obstacles as you progress
- Each level includes CHARACTER, PATH, OBSTACLES, END GATE, press ESC to exit the level. In the right corner, the remaining health is displayed, when health reaches 0, it's GAME OVER!

![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Menu/Menu%201.png)
![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Intro/Intro%201.PNG)
![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Things/gameover.png)
![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Things/complete.png)

## **Key Features**

### **Structure**

- Files are organized by functionality for better system organization and easier debugging

![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Structure.png)

- Core:
  - GameEngine: Manages all systems
  - Graphics: Handles rendering and window management
- Entities:
  - Obstacles: Handles monsters and features (Bat)
  - Player: Handles the playable character
  - Stage: Handles each game level
- States:
  - Game: Handles intro, menu, pause, win, death, etc. (ingame and outgame)
- Systems:

  - Animation: Handles spriteSheet animation
  - Cursor: Draws the mouse and updates position
  - Defs: Basic parameters (screen length, width, etc.)
  - Sounds: Manages audio

- The integration and extension of features in the game becomes flexible. Game loop is tightly organized.

### **Features**

- Level selection feature activated by mouse click

  ![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Menu/level.png)

- Turn on/off sfx/music feature

  ![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Menu/setting%201.png)

- Exit game feature

  ![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Menu/quit%201.png)

- Health reduction feature upon death

  ![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Things/Death/5.png)

- Level exit feature when pressing ESC

  ![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Things/Pause/pause1.png)

### **Victory and Defeat**

- When entering the victory gate

  ![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Things/win.png)

  ![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Things/complete.png)

- When failing (health = 0)

  ![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Things/gameover.png)

### **Characters**

- Knight

  ![image](https://github.com/Nooirpe/GAME/blob/main/Assets/chibi/idle/player.png)

- Monster

  ![image](https://github.com/Nooirpe/GAME/blob/main/Assets/monster/Idle/monster.png)

### **Sound and Graphics**

- Sound plays throughout the game, with sfx for buttons
- Graphics run using spritesheets and images, leading to a smooth experience

## **Credits**

- Game idea, features, and gameplay: Nguyen Le Dung
- Game programming: Nguyen Le Dung
- SDL2.0 library (referenced from [Lazyfoo](https://lazyfoo.net/tutorials/SDL/index.php), [Tianchinchiko](https://www.youtube.com/@tianchinchiko) and class materials)
- Graphics sourced from [Opengameart](https://opengameart.org) and self-designed using [LibreSprite](https://github.com/LibreSprite/libresprite.github.io/blob/master/install.md)
- Music: [Massah](https://www.newgrounds.com/audio/listen/1412555)
- Sound Effects (SFX): from retro sfx on YouTube
- Building references from [Phaser](https://phaser.io/examples/v3.85.0) and [GIVE-UP](https://github.com/NPNLong/GIVE-UP?fbclid=IwY2xjawKGtftleHRuA2FlbQIxMABicmlkETE1eDVEVWlzb1V6dmFURDhuAR6yitnHWqIJapz-Lg82sW0wm4693QIQk0DthdXm7jot79TJv8zGP0d7-2yEfQ_aem_4LRSt8B7oUwCqGvp6azH6A)

---

# **RunMo!**

# **Vietnamese/Tiếng Việt**

## **Giới thiệu**

- Họ và tên: Nguyễn Lê Dũng - K69I - UET

- Mã số sinh viên: 24022633

- Tên game: RunMo!

## **Mô tả**

### **Mô tả chung**

- RunMo! là trò chơi sử dụng ngôn ngữ C++ và SDL2, là sản phẩm cho bài tập lớn của lớp Lập trình nâng cao (2425II_INT2215_12)
- Bạn là một kị sĩ. Tất cả những gì bạn cần làm là vượt qua các chướng ngại vật và tới đích
- Tựa game được lấy ý tưởng và đơn giản hoá từ tựa game "I Wanna Be the Guy: The Movie: The Game (Michael O’Reilly, 2007)"
- Video: [RunMo!](https://youtu.be/JKnO0Bbb6xU)

### **Chi tiết**

- Một phần Intro khi mới vào game
- Menu chính
- Game gồm 3 levels, càng lên level cao càng có thêm tính năng cũng như chướng ngại vật
- Mỗi màn sẽ gồm NHÂN VẬT, ĐƯỜNG ĐI, CHƯỚNG NGẠI VẬT, CỔNG KẾT THÚC, ấn ESC để thoát ra ngoài màn. Bên góc phải màn sẽ hiện lượng máu còn lại, khi máu về 0 sẽ GAME OVER!

![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Menu/Menu%201.png)
![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Intro/Intro%201.PNG)
![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Things/gameover.png)
![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Things/complete.png)

## **Một số điểm nổi bật**

### **Cấu trúc**

- Chia file ra riêng từng mục để hệ thống cũng như dễ dàng hơn trong việc sửa lỗi

![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Structure.png)

- Core:
  - GameEngine: Quản lý tất cả các hệ thống
  - Graphics: Xử lý render và quản lý window
- Entities:
  - Obstacles: Xử lý quái vật và tính năng (Bat)
  - Player: Xử lý nhân vật điều khiển
  - Stage: Xử lý từng màn chơi
- States:
  - Game: Xử lý intro, menu, pause, win, death,... (ingame và outgame)
- Systems:

  - Animation: Xử lý spriteSheet animation
  - Cursor: Vẽ chuột và cập nhật vị trí
  - Defs: 1 số thông số cơ bản (chiều dài, chiều rộng màn hình,...)
  - Sounds: Quản lý âm thanh

- Việc tích hợp và mở rộng các chức năng trong game trở nên linh hoạt. Game loop được tổ chức chặt chẽ.

### **Tính năng**

- Tính năng chọn level khi có event click chuột

  ![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Menu/level.png)

- Tính năng tắt, bật sfx/music

![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Menu/setting%201.png)

- Tính năng thoát game

![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Menu/quit%201.png)

- Tính năng giảm máu khi chết

![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Things/Death/5.png)

- Tính năng thoát màn khi ấn ESC

![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Things/Pause/pause1.png)

### **Chiến thắng và thất bại**

- Khi tiến vào cổng chiến thắng

![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Things/win.png)

![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Things/complete.png)

- Khi thất bại (máu = 0)

![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Things/gameover.png)

### **Nhân vật**

- Kị sĩ

![image](https://github.com/Nooirpe/GAME/blob/main/Assets/chibi/idle/player.png)

- Quái vật

![image](https://github.com/Nooirpe/GAME/blob/main/Assets/monster/Idle/monster.png)

### **Hệ thống âm thanh và đồ hoạ**

- Có âm thanh chạy xuyên suốt cả game, sfx cho các nút

- Đồ hoạ chạy bằng spritesheet cũng như các hình ảnh dẫn tới trải nghiệm mượt mà

## **Credits**

- Ý tưởng game, các chức năng và gameplay: Nguyễn Lê Dũng

- Lập trình game: Nguyễn Lê Dũng

- Thư viện SDL2.0 (tham khảo trên [Lazyfoo](https://lazyfoo.net/tutorials/SDL/index.php), [Tianchinchiko](https://www.youtube.com/@tianchinchiko) và tài liệu trên lớp)

- Đồ hoạ được lấy từ [Opengameart](https://opengameart.org) và tự thiết kế trên [LibreSprite](https://github.com/LibreSprite/libresprite.github.io/blob/master/install.md)

- Âm nhạc: [Massah](https://www.newgrounds.com/audio/listen/1412555)

- Âm thanh (SFX): từ các retro sfx trên youtube

- Tham khảo các cách dựng từ [Phaser](https://phaser.io/examples/v3.85.0) và [GIVE-UP](https://github.com/NPNLong/GIVE-UP?fbclid=IwY2xjawKGtftleHRuA2FlbQIxMABicmlkETE1eDVEVWlzb1V6dmFURDhuAR6yitnHWqIJapz-Lg82sW0wm4693QIQk0DthdXm7jot79TJv8zGP0d7-2yEfQ_aem_4LRSt8B7oUwCqGvp6azH6A)
