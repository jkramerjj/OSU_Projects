#!/usr/bin/env python
# encoding: utf-8

import npyscreen
import sys, psycopg2

#
# class FormObject(npyscreen.Form):
#     def create(self):
#         self.show_atx=40
#         self.show_aty=5
#
#         self.add(npyscreen.TitleText, name="DB Name: ")
#         self.nextrely += 1
#         self.add(npyscreen.TitleText, name="User Name: ", value="Ener User Nmae")
#
#     def afterEditing(self):
#         self.parentApp.setnextForm(None)
#
#
# class FormObject2(npyscreen.SplitForm):
#     def create(self):
#         self.show_atx=40
#         self.show_aty=5
#
#         self.add(npyscreen.TitleText, name="DB Name: ")
#         self.nextrely += 1
#         self.add(npyscreen.TitleText, name="User Name: ", value="Enter User Nmae")
#
#     def afterEditing(self):
#         self.parentApp.setnextForm(None)
#
#
#
#
# class FormObject3(npyscreen.ActionForm, npyscreen.SplitForm, npyscreen.FormWithMenus):
#     def create(self):
#         self.show_atx=40
#         self.show_aty=5
#
#         self.dbName = self.add(npyscreen.TitleText, name="DB Name: ")
#         self.nextrely += 1
#         self.userName = self.add(npyscreen.TitleText, name="User Name: ", value="Ener User Nmae")
#         self.host = self.add(npyscreen.TitleText, name="Host Address:")
#         self.port = self.add(npyscreen.TitleText, name="Port Number: ")
#
#     def afterEditing(self):
#         self.parentApp.setNextForm(None)
#
#     def on_ok(self):
#
#         # self.connection = psycopg2.connect(database=self.dbName, user=self.userName,
#         #                      host=self.host, port=self.port)
#
#         npyscreen.notify_confirm(str(self.connection), "Database Connectin...", editw=1)
#
#         self.pause = "pase"
#
#         #ok Button pressed
#
#     def on_cancel(self):
#         self.dbName.value = " I gotta hi"
#         #cancel pressed






class beginApp(npyscreen.ActionForm, npyscreen.SplitForm, npyscreen.FormWithMenus):
    def create(self):
        self.show_atx=40
        self.show_aty=5

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



class App(npyscreen.NPSAppManaged):
    def onStart(self):
        self.addForm('MAIN', beginApp, name = "Database Interface", lines=10, columns=40, draw_line_at=7)




if  __name__ == "__main__":
    app = App().run()
    print "HI"

