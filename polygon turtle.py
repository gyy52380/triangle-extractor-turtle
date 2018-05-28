import turtle as t

fox ='''
36, 434; 237, 895; 317, 527; #FE8A4F
41, 433; 314, 528; 439, 383; #FF6201
316, 533; 238, 896; 613, 188; #FEB799
237, 900; 172, 1053; 464, 945; #FF6201
240, 895; 609, 709; 610, 347; 522, 352; #FE8A4F
614, 708; 983, 893; 705, 353; 613, 354; #FF6201
612, 710; 240, 895; 609, 971; 981, 896; #FEB799
760, 944; 1044, 1052; 990, 899; #FF6201
989, 892; 908, 530; 1188, 433; #FE8A4F
985, 890; 613, 189; 906, 532; #FEB799
780, 382; 908, 530; 1189, 434; #FF6201
519, 349; 704, 350; 612, 193; #010101
'''

def parse_data(string):
    data = [] #list of tuples [ ((pos, pos, pos), color), ()]...

    lines = string.split('\n')
    print(lines)

    for line in lines:
        if line == '':
            continue
        
        elements = line.split('; ')
        
        polygon = []
        
        color = elements.pop()
        polygon.append(color)
        
        for str_pos in elements:
            "10, 20"
            point = [float(i)/4 for i in str_pos.split(', ')]
            polygon.append(point)
            
        data.append(polygon)

    return data
    
def draw_polygon(color, vertices): #list of tuples, hex string
    #print("vertices", vertices)
    t.pu()
    t.begin_fill()
    t.color(color, color)
    t.setpos(vertices[0][0], vertices[0][1])
    t.pd()
    for i in range(1, len(vertices)):
        #print("color", color)
        #print("pos", vertices[i][0], vertices[i][1])
        t.setpos(int(vertices[i][0]), int(vertices[i][1]))
    t.setpos(vertices[0][0], vertices[0][1])
    t.end_fill()
    t.pu()


t.width(2)
data = parse_data(fox)
for i in data:
    draw_polygon(i[0], i[1:])

