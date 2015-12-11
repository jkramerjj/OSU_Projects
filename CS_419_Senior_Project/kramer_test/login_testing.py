#!/usr/bin/env python
# encoding: utf-8

import npyscreen
import curses
import sys, psycopg2


class FormObject4(npyscreen.ActionForm,  npyscreen.FormWithMenus):
    def create(self):

        self.dbName = self.add(npyscreen.TitleText, name="DB Name: ")
        self.nextrely += 1
        self.userName = self.add(npyscreen.TitleText, name="User Name: ", value="Ener User Nmae")
        self.host = self.add(npyscreen.TitleText, name="Host Address:")
        self.port = self.add(npyscreen.TitleText, name="Port Number: ")

        self.menu = self.new_menu(name="Main Menu", shortcut='m')
        self.menu.addItem("Item 1", self.press_1, "1")
        self.menu.addItem("Item 2", self.press_2, "2")
        self.menu.addItem("Exit Form", self.exit_form, "^X")

        self.submenu = self.menu.addNewSubmenu("A sub menu", 's')
        self.submenu.addItem("WOO")


    def press_1(self):
        npyscreen.notify_confirm("You pressed Item1!", "Item 1", editw=1)

    def press_2(self):
        npyscreen.notify_confirm("You pressed Item2!", "Item 2", editw=1)

    def exit_form(self):
        npyscreen.notify_confirm("You pressed Exit!", "Exit", editw=1)
        self.parentApp.setNextForm(None)

    def afterEditing(self):
        self.parentApp.setNextForm(None)

    def on_ok(self):

        # self.connection = psycopg2.connect(database=self.dbName, user=self.userName,
        #                      host=self.host, port=self.port)

        npyscreen.notify_confirm("DB Connecting", "Database Connectin...", editw=1)
        self.parentApp.setNextForm(None)


    def on_cancel(self):
        self.dbName.value = " I gotta hi"
        #cancel pressed





class StartApp(npyscreen.FormWithMenus, npyscreen.NPSAppManaged,
               npyscreen.apNPSApplication.NPSApp):
    # def __init__(self, *args, **keywords):
    #     super(StartApp, self).__init__(*args, **keywords)
    #     self.dbName = None
    def create(self):

        #self.add(npyscreen.TitleFixedText, editable="False", name="Database Interface", value="Please Press Control L or ^L to log in.", color='WARNING', labelColor='LABEL')
        self.dbNames = self.add(npyscreen.TitleSelectOne, editable=False, name="Database Options",
                               values=['LogIn', 'View Tables'], scroll_exit=True)
        # self.nextrely += 1
        #self.userName = self.add(npyscreen.TitleText, name="User Name: ", value="Enter User Name")
        # if self.userName == "YES":
        #     self.parentApp.switchForm("LOGIN")

        #self.host = self.add(npyscreen.TitlePassword, name="Host Address:")
        # self.port = self.add(npyscreen.TitleText, name="Port Number: ")

       # self.multiLine = self.add(npyscreen.MultiLineEdit, name="Line Editing", value="Enter lines here")
       # self.parentApp.setNextForm("LOGIN")
        #self.parentApp.NEXT_ACTIVE_FORM = "LOGIN"
        self.menu = self.new_menu(name="Menu Access", shortcut='^M')

        self.shouldIChange = False
        # self.submenu = self.menu.addNewSubmenu("Log In ", 'L')
        # self.dbName = self.submenu.addItem(npyscreen.TitleText, name="Db Name")

        self.menu.addItem("Login", self.login_selected, "L")
        self.menu.addItem("Item 2", self.press_2, "2")
        self.menu.addItem("Exit Program", self.exit_form, "^Q")

        #self.submenu = self.menu.addNewSubmenu("A sub menu", 's', preDisplayFunction=self.test_function())
        #self.submenu.addItem("WOO")
        if self.shouldIChange == True:
            self.parentApp.NEXT_ACTIVE_FORM = "LOGIN"

        self.switchForm("LOGIN")
    #
    # def switchForm(self):
    #     self.editing = False
    #     self.setNextForm("LOGIN")
    #     self.switchFormNow()
    #     self.activeForm = "LOGIN"
    #     #self.parentApp.NEXT_ACTIVE_FORM = "LOGIN"



    def login_selected(self):
        #npyscreen.notify_confirm("You pressed Item1!", "Item 1", wide=True, editw=1)
        #self.parentApp.change_form('LOGIN')
        #self.shouldIChange = True
        #self.switchForm("LOGIN")

        pass

    def press_2(self):
        npyscreen.notify_confirm("You pressed Item2!", "Item 2", editw=1)

    def exit_form(self):
        #npyscreen.notify_confirm("You pressed Exit!", "Exit", editw=1)
        self.parentApp.switchForm(None)

    def afterEditing(self):
        self.parentApp.setNextForm(None)

    def on_ok(self):

        # self.connection = psycopg2.connect(database=self.dbName, user=self.userName,
        #                      host=self.host, port=self.port)

        npyscreen.notify_confirm("DB Connecting", "Database Connectin...", editw=1)
        self.parentApp.setNextForm(None)


    def on_cancel(self):
        self.dbName.value = " I gotta hi"
        #cancel pressed

    def test_function(self):
        npyscreen.notify_confirm("Welcome Please Log In", "Please Log-In", wide=True, editw=1)
        self.submenu.addItem("WOO")


class loginApplication(npyscreen.FormWithMenus):
    def create(self):
        # self.dbNames = self.add(npyscreen.TitleSelectOne, editable=False, name="Database Options",
        #                        values=['LogIn', 'View Tables'], scroll_exit=True)
        self.nextrely += 1
        self.userName = self.add(npyscreen.TitleText, name="User Name: ", value="Enter User Name")
        self.host = self.add(npyscreen.TitlePassword, name="Host Address:")
        self.port = self.add(npyscreen.TitleText, name="Port Number: ")



class App(npyscreen.NPSAppManaged):
    def onStart(self):
        self.addForm('MAIN', StartApp, name = "Database Interface")
        self.addForm('LOGIN', loginApplication, name="LOGIN!!!")
        #self.addForm('MAIN', FormObject4, name = "Database Log In", lines=10, columns=40, draw_line_at=7)


        #x = "PAUSE"




if  __name__ == "__main__":
    app = App().run()


