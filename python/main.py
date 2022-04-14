from matplotlib.figure import Figure
import tkinter as tk
from pandas import DataFrame
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg


def tk_matplotlib():
    from iir_filter import generate_coefficients, generate_filterbank, mfreqz, impz
    from iir_filter import SAMPTPL, FILT_TUPLE, COEFF_TUPLE
    center_freqs = [100, 400, 800, 1200, 2000, 4000, 8000, 16000]
    passband = 0.5
    transition = 0.25
    # Sampling frequency in Hz
    Fs = 48000
    Ap = 1
    As = 40
    filterbank = generate_filterbank(
        center_freqs=center_freqs, passband=passband, transition=transition)
    # Compute pass band and stop band edge frequencies
    # Normalized passband edge
    # frequencies w.r.t. Nyquist rate
    for bp in filterbank:
        band_pass_filter = generate_coefficients(bp, Fs, Ap, As)

    data1 = {'Center_Freqs': center_freqs,
             'band_pass': filterbank}
    df1 = DataFrame(data1, columns=['Center_Freqs', 'band_pass'])
    data2 = {'Year': [1920, 1930, 1940, 1950, 1960, 1970, 1980, 1990, 2000, 2010],
             'Unemployment_Rate': [9.8, 12, 8, 7.2, 6.9, 7, 6.5, 6.2, 5.5, 6.3]
             }
    df2 = DataFrame(data2, columns=['Year', 'Unemployment_Rate'])
    data3 = {'Interest_Rate': [5, 5.5, 6, 5.5, 5.25, 6.5, 7, 8, 7.5, 8.5],
             'Stock_Index_Price': [1500, 1520, 1525, 1523, 1515, 1540, 1545, 1560, 1555, 1565]
             }
    df3 = DataFrame(data3, columns=['Interest_Rate', 'Stock_Index_Price'])
    root = tk.Tk()
    figure1 = plt.Figure(figsize=(6, 5), dpi=100)
    ax1 = figure1.add_subplot(111)
    bar1 = FigureCanvasTkAgg(figure1, root)
    bar1.get_tk_widget().pack(side=tk.LEFT, fill=tk.BOTH)
    df1 = df1[['Country', 'GDP_Per_Capita']].groupby('Country').sum()
    df1.plot(kind='bar', legend=True, ax=ax1)
    ax1.set_title('Country Vs. GDP Per Capita')

    figure2 = plt.Figure(figsize=(5, 4), dpi=100)
    ax2 = figure2.add_subplot(111)
    line2 = FigureCanvasTkAgg(figure2, root)
    line2.get_tk_widget().pack(side=tk.LEFT, fill=tk.BOTH)
    df2 = df2[['Year', 'Unemployment_Rate']].groupby('Year').sum()
    df2.plot(kind='line', legend=True, ax=ax2,
             color='r', marker='o', fontsize=10)
    ax2.set_title('Year Vs. Unemployment Rate')

    figure3 = plt.Figure(figsize=(5, 4), dpi=100)
    ax3 = figure3.add_subplot(111)
    ax3.scatter(df3['Interest_Rate'], df3['Stock_Index_Price'], color='g')
    scatter3 = FigureCanvasTkAgg(figure3, root)
    scatter3.get_tk_widget().pack(side=tk.LEFT, fill=tk.BOTH)
    ax3.legend(['Stock_Index_Price'])
    ax3.set_xlabel('Interest Rate')
    ax3.set_title('Interest Rate Vs. Stock Index Price')

    root.mainloop()


def tk_gui():
    import tkinter as tk

    root = tk.Tk()

    canvas1 = tk.Canvas(root, width=800, height=300)
    canvas1.pack()

    label1 = tk.Label(root, text='Graphical User Interface')
    label1.config(font=('Arial', 20))
    canvas1.create_window(400, 50, window=label1)

    entry1 = tk.Entry(root)
    canvas1.create_window(400, 100, window=entry1)

    entry2 = tk.Entry(root)
    canvas1.create_window(400, 120, window=entry2)

    entry3 = tk.Entry(root)
    canvas1.create_window(400, 140, window=entry3)

    def create_charts():
        global x1
        global x2
        global x3
        global bar1
        global pie2
        x1 = float(entry1.get())
        x2 = float(entry2.get())
        x3 = float(entry3.get())

        figure1 = Figure(figsize=(4, 3), dpi=100)
        subplot1 = figure1.add_subplot(111)
        xAxis = [float(x1), float(x2), float(x3)]
        yAxis = [float(x1), float(x2), float(x3)]
        subplot1.bar(xAxis, yAxis, color='lightsteelblue')
        bar1 = FigureCanvasTkAgg(figure1, root)
        bar1.get_tk_widget().pack(side=tk.LEFT, fill=tk.BOTH, expand=0)

        figure2 = Figure(figsize=(4, 3), dpi=100)
        subplot2 = figure2.add_subplot(111)
        labels2 = 'Label1', 'Label2', 'Label3'
        pieSizes = [float(x1), float(x2), float(x3)]
        my_colors2 = ['lightblue', 'lightsteelblue', 'silver']
        explode2 = (0, 0.1, 0)
        subplot2.pie(pieSizes, colors=my_colors2, explode=explode2,
                     labels=labels2, autopct='%1.1f%%', shadow=True, startangle=90)
        subplot2.axis('equal')
        pie2 = FigureCanvasTkAgg(figure2, root)
        pie2.get_tk_widget().pack()

    def clear_charts():
        bar1.get_tk_widget().pack_forget()
        pie2.get_tk_widget().pack_forget()

    button1 = tk.Button(root, text=' Create Charts ', command=create_charts,
                        bg='palegreen2', font=('Arial', 11, 'bold'))
    canvas1.create_window(400, 180, window=button1)

    button2 = tk.Button(root, text='  Clear Charts  ', command=clear_charts,
                        bg='lightskyblue2', font=('Arial', 11, 'bold'))
    canvas1.create_window(400, 220, window=button2)

    button3 = tk.Button(root, text='Exit Application', command=root.destroy,
                        bg='lightsteelblue2', font=('Arial', 11, 'bold'))
    canvas1.create_window(400, 260, window=button3)

    root.mainloop()


def main():
    tk_gui()


if __name__ == "__main__":
    main()
