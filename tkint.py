import tkinter as tk
from tkinter.ttk import *
import subprocess
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.collections import LineCollection

top = tk.Tk()
top.title("Mesh generation")
V1=tk.StringVar()
V2=tk.StringVar()
V3=tk.StringVar()
V4=tk.StringVar()
V5=tk.StringVar()
V6=tk.StringVar()
def submit():
   print('bridging...')
   subprocess.call(["g++","2Dgrid.cpp"])
   subprocess.call(["./a.out",E1.get(),E2.get(),E3.get(),E4.get(),E5.get(),E6.get()])
   """V1.set("")
   V2.set("")
   V3.set("")
   V4.set("")
   V5.set("")
   V6.set("")"""
   x, y = np.meshgrid(np.linspace(0,int(E1.get()), int(E3.get())), np.linspace(0, int(E2.get()), int(E4.get())))
   plt.scatter(x, y)
   segs1 = np.stack((x,y), axis=2)
   segs2 = segs1.transpose(1,0,2)
   plt.gca().add_collection(LineCollection(segs1))
   plt.gca().add_collection(LineCollection(segs2))
   plt.show()
   f=open("buffertext.txt","r")
   s=""
   for x in f:
     s=s+x
   new=tk.Toplevel(top)
   new.title("Mesh information")
   new.geometry("700x700")
   tk.Label(new,text=s).pack(pady=20,padx=20)
L1 = tk.Label(top,text="Dimension along x axis in mm")
L1.pack()
E1 = tk.Entry(top,textvariable=V1)
E1.pack()
L2 = tk.Label(top, text="Dimension along y axis in mm")
L2.pack()
E2 = tk.Entry(top, textvariable=V2)
E2.pack()
L3 = tk.Label(top, text="Points along x axis")
L3.pack()
E3 = tk.Entry(top, textvariable=V3)
E3.pack()
L4 = tk.Label(top, text="Points along y axis")
L4.pack()
E4 = tk.Entry(top, textvariable=V4)
E4.pack()
L5 = tk.Label(top, text="X index of the cell")
L5.pack()
E5 = tk.Entry(top, textvariable=V5)
E5.pack()
L6 = tk.Label(top, text="Y index of the cell")
L6.pack()
E6 = tk.Entry(top, textvariable=V6)
E6.pack()
b=tk.Button(top,text="Submit",bg="red",command=submit)
b.pack()

top.mainloop()
