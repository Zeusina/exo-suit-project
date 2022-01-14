from PyQt5 import QtWidgets, uic
from PyQt5.QtSerialPort import QSerialPort, QSerialPortInfo
from PyQt5.QtCore import QIODevice, qsrand
#Импортируем все библиотеки

app = QtWidgets.QApplication([])  #Создаем тело приложения
ui = uic.loadUi("design.ui") #Подгружаем интерфейс приложения
ui.setWindowTitle("Мониториг датчиков") #Изменяем заголовок приложения

serial = QSerialPort() #Содаем тело, которое взаимодействует с COM
serial.setBaudRate(9600) #Задаем Боды

portlist = [] #Список портов для выпадающего списка
ports = QSerialPortInfo().availablePorts() #Получаем информацию о всех доступных блоках
for port in ports: #Из всей информации достаем название портов
    portlist.append(port.portName()) # Прибавляем названия портов к текущему значению в списке
ui.ComS.addItems(portlist) #Отображаем полученный список портов в визуальном интерфейсе

def OnOpen(): #Создаем функцию для открытия COM порта
    serial.setPortName(ui.ComS.currentText()) #Задаем имя порта из списка
    serial.open(QIODevice.ReadWrite) #Открываем COM порт

def OnClose(): #Создаем функию для закрытия COM порта
    serial.close() #Закрываем COM порт

def onRead(): #Создаем функцию для работы с последовательным портом
    rx = int(str(serial.readLine(), 'utf-8')) # Создаем переменную и присваиваем ей значения считываемые из COM
    print(rx)

ui.COMO.clicked.connect(OnOpen) #По нажатию кнопки OPEN вызываем функцию открытия порта
ui.COMC.clicked.connect(OnClose) #По нажатию кнопки CLOSE вызываем функцию закрытия порта
serial.readyRead.connect(onRead)

ui.show() #Отображаем интерфейс
app.exec() #Запускаем приложение