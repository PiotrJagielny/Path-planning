# Path-planning
This is the application where i implemented an A-star path finding algorithm, and made visualization for the process of finding the shortest path.
I used C++ with SFML.

Here i will show features of this app.

This is main page that pops up on application start
![image](https://user-images.githubusercontent.com/76881722/228042879-dfc1ff29-2cd8-4d21-8cf1-17e8e2735d53.png)

There are three buttons. If map generator button is marked means that some tiles will be automatically put on the map randomly.
When entered on the visualization stage, there is possibility of adding and removing obstacles, and changing start and end points on the map.

First type of mode of visualization is Static mode. This means that the algorithm will execute slowly so that you can see the process of finding shortest path.

Setting end and start points
![image](https://user-images.githubusercontent.com/76881722/228043820-3a42d0aa-93ce-4ccd-8e35-3e14b50632d0.png)
Process of finding shortest path
![image](https://user-images.githubusercontent.com/76881722/228044577-c0257810-a23e-443a-9575-671634d8f0cc.png)
Shortest path was found
![image](https://user-images.githubusercontent.com/76881722/228044676-c6f73b57-0004-4959-ba54-28fd7c50a509.png)

There is also Dynamic mode, where you firstly set start and end points, and then the path will update as you add new obsticles

Start and end points set. The shortest path appeared
![image](https://user-images.githubusercontent.com/76881722/228045025-13db7611-378d-4230-a777-7aed558ed590.png)
The path is updating with new obstacles adding
![image](https://user-images.githubusercontent.com/76881722/228045149-72a87f05-da92-41f1-889a-d5696df1bb4d.png)



