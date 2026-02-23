# raycast_practice

https://github.com/365kim/raycasting_tutorial/blob/master/3_untextured_raycaster.md <br>
https://sikpang.tistory.com/32


### 발견된 버그

draw_textured_wall함수
-> DDA algorithm에서 perpwalldist가 1미만일 때, 그에 따른 texture위치를 수정하지 않고 window_height에 맞게 draw하여서 퍼져보이는 현상이 발견됨

- 수정 결과
```
double	line_h = (double)(WIN_HEIGHT / perpwalldist);
double	step = (double)(t->h / line_h);
//이 부분이 추가됨.
double	tex_pos = (draw_start - WIN_HEIGHT / 2.0 + line_h / 2.0) * step;
```

raycast.c
raycast_frame 함수
dir을 움직이지 않은 채로 직진하게 될 경우 perpwalldist == 0이 되어 벽을 뚫고 보는 경우가 있었음.

- 수정 결과
```
if (perpwalldist <= 0.001)
	perpwalldist = 0.001;
```
