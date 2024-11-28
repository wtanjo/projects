import tkinter as tk

w=tk.Tk()
w.title("my window")
w.geometry("800x750")
var1=tk.StringVar()                            #创建变量
l=tk.Label(w,textvariable=var1,bg='yellow',width=15,height=4)
l.pack()

var2=tk.StringVar()
var2.set([1,2,3,4,5])
lb=tk.Listbox(w,listvariable=var2)
lb.pack()

def print_selection():
    v=lb.get(lb.curselection())                #获取listbox中的当前选中的项的值
    var1.set(v)

b=tk.Button(w,text="current selection",command=print_selection)
b.pack()

t=tk.Text(w,height=2)
t.pack()
w.mainloop()