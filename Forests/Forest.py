from tkinter import *
from tkinter import ttk
import random
import fileinput
#import fileoutput
import subprocess
width=50
height=50
#options: Forest fires, show saplings
class Grid:
    def __init__(self,width,height):
        self.grid=[[Cell(i,j,0,self,1) for j in range(0,height)]for i in range(0,width)]
    def update(self):
        for row in self.grid:
            for cell in row:
                cell.update()
        for row in self.grid:
            for cell in row:
                cell.finishUpdate()
    def get(self, x, y):
        return self.grid[x][y]
    def getGrid(self):
        return self.grid
class Cell:     
    def __init__(self,x,y,growth, grid,growthFactor):
        self.x=x
        self.y=y
        self.growth=growth
        self.grid=grid
        self.newState=growth
        self.age=0
        self.growthFactor=growthFactor
    def update(self):
        global fires
        neighbors=self.mooreNeighbors()
        sapneighbors=0
        growneighbors=0
        matneighbors=0
        fireneighbors=0
        global random
        global rindex
        if (self.growth!=0):
            self.age+=1
        else:
            self.age=0
        for cell in neighbors:
            if cell.growth==1:
               sapneighbors+=1
            elif cell.growth==2:
                growneighbors+1
            elif cell.growth==3:
                matneighbors+=1
            elif cell.growth==4:
                fireneighbors+=1
        if self.growth==0 and self.growthFactor>waterheight:
            if matneighbors>0 and matneighbors<(1/(.8*self.growthFactor)):
                rand=randomlist[rindex]
                rindex=(rindex+1)%100000
                if rand<.05*matneighbors:
                    self.newState=1
        elif self.growth==1:
            rand=randomlist[rindex]
            rindex=(rindex+1)%100000
            if (rand<.3):
                self.newState=2
            if (matneighbors>0):
                rand=random.random()
                if rand<.8*matneighbors*self.growthFactor:
                    self.newState=0
        elif self.growth==2:
            rand=randomlist[rindex]
            rindex=(rindex+1)%100000
            if (rand<.1):
                self.newState=3
        elif self.growth==4:
            rand=randomlist[rindex]
            rindex=(rindex+1)%100000
            if rand<.3:
                self.newState=0
        if fires.get() and self.growth!=0:
            rand=randomlist[rindex]
            rindex=(rindex+1)%100000
            if rand<.0001:
                self.newState=4
            elif self.growth==3 and rand<fireneighbors*.1*(self.age/200.0):
                self.newState=4
               
            elif self.growth!=3 and self.growth!=4 and fireneighbors>0:
                self.newState=4
        
            
    def finishUpdate(self):
        self.growth=self.newState
    def setGrowth(self,growth):
        self.growth=growth
        self.newState=growth
    def mooreNeighbors(self):
        neighbors=[]
        for i in range(-1,2):
            for j in range(-1,2):
                if not(i==0 and j==0) and self.x+i>=0 and self.x+1<width and self.y+j>=0 and self.y+j<height:
                   neighbors.append(self.grid.get(self.x+i,self.y+j))
        return neighbors

def drawAll():
    global grid
    canvas.delete("all")
    horz=canvas.winfo_width()/width
    startx=0
    vert=canvas.winfo_height()/height
    starty=0
    for i in range(0,width):
        canvas.create_line(startx, canvas.winfo_height(), startx, 0)
        startx+=horz
    for i in range(0,height):
        canvas.create_line(canvas.winfo_width(),starty, 0, starty)
        starty+=vert
    global waterheight
    global showsaplings
    for row in grid.getGrid():
        for cell in row:
            if cell.growth==1 and showsaplings.get():
                canvas.create_rectangle(cell.x*horz,cell.y*vert,cell.x*horz+horz,cell.y*vert+vert,fill='light green')
            elif cell.growth==2:
                canvas.create_rectangle(cell.x*horz,cell.y*vert,cell.x*horz+horz,cell.y*vert+vert,fill='green')
            elif cell.growth==3:
                canvas.create_rectangle(cell.x*horz,cell.y*vert,cell.x*horz+horz,cell.y*vert+vert,fill='dark green')
            elif cell.growth==4:
                canvas.create_rectangle(cell.x*horz,cell.y*vert,cell.x*horz+horz,cell.y*vert+vert,fill='red')
            else:
                if cell.growthFactor<waterheight:
                    canvas.create_rectangle(cell.x*horz,cell.y*vert,cell.x*horz+horz,cell.y*vert+vert,fill='light blue')
                else:
                    #gray from 50-100
                    low=50
                    high=100
                    grayFactor=(cell.growthFactor-waterheight)*(high-low)+low
                    canvas.create_rectangle(cell.x*horz,cell.y*vert,cell.x*horz+horz,cell.y*vert+vert,fill='gray'+str(int(grayFactor)))
                
                    
                
    
def update():
    global running
    if running:
        global grid
        grid.update()
        global frameskip
        global currentframe
        if (int(frameskip.get())==0):
            drawAll()
        else:
            currentframe=(currentframe+1) % int(frameskip.get())
            if currentframe==0:
                drawAll()
        global simspeed
        root.after(int(simspeed.get()),update)
    
def start():
    global running
    global randomlist
    global rindex
    randomlist=[]
    for i in range(0,100000):
        randomlist.append(random.random())
    rindex=0
    if not(running):
        root.after(100,update)
        running=True
def generate():
    subprocess.call(["./Terrain Generator.exe"])
    initSim()
    drawAll()
    
def initSim():
        #setup simulation
    global grid
    grid=Grid(width,height)
    heightgrid= [[0 for j in range (0,height)] for i in range(0,width)]
    global waterheight
    heightmap = fileinput.input("./Data/heightmap.txt")
    rownum=0
    for line in heightmap:
        if heightmap.isfirstline():
            waterheight=float(line)
        else:
            data=line.split(" ")
            columnnum=0
            for spot in data:
                if spot != '\n':
                    heightgrid[rownum][columnnum]=spot
                    columnnum+=1
            rownum+=1
    low=10000
    high=-10000
    for row in heightgrid:
        for column in row:
            if float(column)<low:
                low=float(column)
            if float(column)>high:
                high=float(column)
    rownum=0
    waterheight=(float(waterheight)-low)/(high-low)
    for row in heightgrid:
        columnnum=0
        for column in row:
            
            grid.get(rownum,columnnum).growthFactor=(float(column)-low)/(high-low)
            columnnum+=1
        rownum+=1
    for i in range(0,5):
        randx=random.randint(0,width-1)
        randy=random.randint(0,height-1)
        cell=grid.get(randx,randy)
        if (cell.growthFactor>waterheight):
            cell.setGrowth(3)
        else:
            i+=-1
    drawAll()
    
def pause():
    global running
    running=False

def resume():
    global running
    running=True
    root.after(100,update)
def export():
        f=open('./Data/treeMap.txt','w')
        for row in grid.getGrid():
            for cell in row:
                f.write(str(cell.growth))
                f.write(' ')
            f.write('\n')
        f.close()
                
def render():
    export()
    subprocess.call("ForestRenderer.exe")
root = Tk()
root.title("Foresty Generator")
root.columnconfigure(0, weight=1,minsize=640)
root.rowconfigure(0, weight=1,minsize=640)

mainframe = ttk.Frame(root, padding="3")
mainframe.grid(column=0, row=0, sticky=(N, W, E, S))
mainframe.columnconfigure(0, weight=1)
mainframe.rowconfigure(0, weight=1)
mainframe.columnconfigure(1, weight=10)
mainframe.rowconfigure(1, weight=10)

bottomLeft=ttk.Frame(mainframe)
bottomLeft.grid(column=0,row=1,sticky=(N,W,E,S),padx=1,pady=1,columnspan=2)
bottomLeft.columnconfigure(0,weight=10)
bottomLeft.rowconfigure(0,weight=10)
bottomLeft['borderwidth']=2;
bottomLeft['relief'] = 'sunken'
canvas=Canvas(bottomLeft,bg='white')
canvas.rowconfigure(0,weight=1)
canvas.columnconfigure(0,weight=1)
canvas.grid(column=0,row=0,sticky=(N,W,E,S))

topLeft=ttk.Frame(mainframe)
topLeft.columnconfigure(0,weight=1)
topLeft.grid(column=0,row=0,sticky=(N, E))
ttk.Button(topLeft,text="Generate Terrain", command=generate).grid()
ttk.Button(topLeft,text="Start",command=start).grid(column=1,row=0)
ttk.Button(topLeft,text="Pause",command=pause).grid(column=1,row=1)
ttk.Button(topLeft,text="Resume",command=resume).grid(column=1,row=2)
#ttk.Button(topLeft,text="Export State",command=export).grid()
ttk.Button(topLeft,text="Render State",command=render).grid()

right=ttk.Labelframe(mainframe,text="variables")
right['borderwidth']=2;
right['relief'] = 'sunken'
right.grid(column=1,row=0,sticky=(N, W))
right.columnconfigure(0,weight=5)
first=StringVar()

global fires, showsaplings, frameskip, simspeed, growthspeed
fires=BooleanVar()
fires.set(True)
showsaplings=BooleanVar()
showsaplings.set(True)
frameskip=StringVar()
frameskip.set("0")
simspeed=StringVar()
simspeed.set("10")
first_entry=ttk.Checkbutton(right,text="Fire",variable=fires)
first_entry.grid(column=1,row=0,sticky=(N,W))
second_entry=ttk.Checkbutton(right,text="Show Saplings",variable=showsaplings)
second_entry.grid(column=1,row=1,sticky=(N,W))
ttk.Label(right,text="Frame Skip").grid(column=2,row=0,sticky=(N,W))
third_entry=ttk.Entry(right,textvariable=frameskip)
third_entry.grid(column=3,row=0,stick=(N,W))
ttk.Label(right,text="sim speed in ms").grid(column=2,row=1,sticky=(N,W))
fourth_entry=ttk.Entry(right,textvariable=simspeed)
fourth_entry.grid(column=3,row=1,stick=(N,W))



#ttk.Label(right,text="look").grid(column=0,row=0,sticky=(N,W))

global currentframe
currentframe=0
global running


running=False
root.mainloop()

