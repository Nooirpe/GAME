# **RunMo!**

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
- Mỗi màn sẽ gồm NHÂN VẬT, ĐƯỜNG ĐI, TƯỜNG, CỔNG KẾT THÚC, ấn ESC để thoát ra ngoài màn. Bên góc phải màn sẽ hiện lượng máu còn lại, khi máu về 0 sẽ GAME OVER!

![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Menu/Menu%201.png)
![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Intro/Intro%201.PNG)
![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Things/gameover.png)
![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Things/complete.png)

## **Một số điểm nổi bật**

### **Cấu trúc**

- Chia file ra riêng từng mục để hệ thống cũng như dễ dàng hơn trong việc sửa lỗi

![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Structure.png)

- Việc tích hợp và mở rộng các chức năng trong game trở nên linh hoạt. Game loop được tổ chức chặt chẽ.

### **Tính năng**

- Tính năng tắt, bật sfx/music

![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Menu/setting%201.png)

- Tính năng thoát game

![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Menu/quit%201.png)

- Tính năng giảm máu khi chết

![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Things/Death/5.png)

- Tính năng chia level khi có event click chuột
  ![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Menu/level.png)

- Tính năng thoát màn khi ấn ESC

![image](https://github.com/Nooirpe/GAME/blob/main/Assets/Things/Pause/pause1.png)

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

- Tham khảo các cách dựng từ [Phaser](https://phaser.io/examples/v3.85.0)
