
import sys
from PyQt4 import QtCore, QtGui
from design import Ui_MainWindow

from impl import calculate_first, term_and_nonterm, get_augmented , find_states, combine_states, get_parse_table
from  state import State, lalrState

class parser(QtGui.QMainWindow):
    def __init__(self, parent = None):
        QtGui.QWidget.__init__(self,parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.setFixedSize(852, 671)
        self.setWindowTitle("LALR Parser")

        self.init()

        QtCore.QObject.connect(self.ui.action_Open,QtCore.SIGNAL("triggered()"),self.open_file)
        self.ui.action_Exit.triggered.connect(self.exit_app)
        self.ui.display.clicked.connect(self.disp)
        self.ui.first.clicked.connect(self.disp_first)
        self.ui.lr1.clicked.connect(self.disp_lr1_states)
        self.ui.lalr.clicked.connect(self.disp_lalr_states)
        self.ui.parse_table.clicked.connect(self.disp_parse_table)
        self.ui.plainTextEdit.textChanged.connect(self.check_changed)
        self.ui.parse.clicked.connect(self.disp_parsing)
        self.ui.actionAuthor.triggered.connect(self.disp_author)


    def init(self):
        self.grammar = []
        self.augment_grammar = []
        self.first = {}
        self.term = []
        self.non_term = []
        self.states = []
        self.lalr_states = []
        self.parse_table = []
        State.state_count = -1
        lalrState.state_count = 0

    def check_changed(self):
        self.changed = True


    def open_file(self):
        file = QtGui.QFileDialog.getOpenFileName(self,'Open Grammar file')
        if file != '':
            file = open(file,'r')
            self.ui.plainTextEdit.setPlainText(file.read())
            file.close()
            self.ui.lineEdit.clear()
            self.ui.textBrowser.clear()


    def read_input(self):
        self.init()
        lines = self.ui.plainTextEdit.toPlainText()         #string
        lines_list = lines.split('\n')                      #converting into list of lines

        try:
            for line in lines_list:
                line = line.replace(' ' ,'')
        
                if line != '':
                    line_list = line.split('->')
        
                    if line_list[0].isupper() and line_list[1] != '':
                        if '|' in line_list[1]:
                            prod_list = line_list[1].split('|')
                            for prod in prod_list:
                                self.grammar.append([line_list[0],prod])
                        else:
                            self.grammar.append(line_list)
                    else:
                        self.ui.textBrowser.clear()
                        self.ui.textBrowser.setText("Invalid grammar")
                        self.grammar = []
    
            if self.grammar != []:
                term_and_nonterm(self.grammar,self.term,self.non_term)
                calculate_first(self.grammar,self.first,self.term,self.non_term)
                get_augmented(self.grammar,self.augment_grammar)
                find_states(self.states,self.augment_grammar,self.first,self.term,self.non_term)
                combine_states(self.lalr_states, self.states)
                get_parse_table(self.parse_table,self.lalr_states,self.augment_grammar)
                self.changed = False

        except (KeyError, IndexError):
            self.ui.textBrowser.clear()
            self.ui.textBrowser.setText("Invalid grammar")
            self.init()
            


############################         DISPLAY          ################################

    def disp(self):
        self.ui.textBrowser.clear()
        if self.grammar == [] or self.changed:
            self.read_input()

        if self.grammar != []:
            for prod in self.grammar:
                s =  prod[0]+ ' -> ' + prod[1]+'\n'
                self.ui.textBrowser.append(s)
            self.ui.textBrowser.append("\nNon Terminals : "+' '.join(self.non_term)+"\nTerminals : "+' '.join(self.term))
        

    def disp_first(self):
        if self.first == {} or self.changed:
            self.read_input()
        if self.first != {}:
            self.ui.textBrowser.clear()
            for nonterm in self.non_term:
                self.ui.textBrowser.append('First('+nonterm+') : '+' '.join(self.first[nonterm])+'\n')


    def disp_lr1_states(self):
        if self.states == [] or self.changed:
            self.read_input()
        if self.states != []:
            self.ui.textBrowser.clear()
            self.ui.textBrowser.append("Number of LR(1) states : "+ str(self.states[len(self.states)-1].state_num + 1))
            for state in self.states:
                self.ui.textBrowser.append('----------------------------------------------------------------')
                if state.state_num == 0:
                    self.ui.textBrowser.append("\nI"+str(state.state_num)+' : '+'\n')
                else:
                    self.ui.textBrowser.append("\nI"+str(state.state_num)+' : '+' goto ( I'+str(state.parent[0])+" -> '"+ str(state.parent[1]) +"' )\n")
                for item in state.state:
                    self.ui.textBrowser.append(item[0]+ ' -> ' + item[1]+' ,  [ '+ ' '.join(item[2])+' ]')
                if state.actions != {}:
                    self.ui.textBrowser.append('\nActions : ')
                    for k,v in state.actions.items():
                        self.ui.textBrowser.insertPlainText(str(k)+' -> '+str(abs(v))+'\t')



    def disp_lalr_states(self):
        if self.lalr_states == [] or self.changed:
            self.read_input()
        if self.lalr_states != []:
            self.ui.textBrowser.clear()
            self.ui.textBrowser.append("Number of LALR states : " + str(lalrState.state_count))
            for state in self.lalr_states:
                self.ui.textBrowser.append('----------------------------------------------------------------')
                if state.state_num == 0:
                    self.ui.textBrowser.append("\nI"+str(state.state_num)+' : '+'\tGot by -> '+str(state.parent_list)+'\n')
                else:
                    self.ui.textBrowser.append("\nI"+str(state.state_num)+' : '+' goto ( I'+str(state.parent[0])+" -> '"+ str(state.parent[1]) +"' )"+'\tGot by -> '+str(state.parent_list)+'\n')
                for item in state.state:
                    self.ui.textBrowser.append(item[0]+ ' -> ' + item[1]+' ,   [ '+ ' '.join(item[2])+' ]')
                if state.actions != {}:
                    self.ui.textBrowser.append('\nActions : ')
                    for k,v in state.actions.items():
                        self.ui.textBrowser.insertPlainText(str(k)+' -> '+str(abs(v))+'\t')



    def disp_parse_table(self):
        if self.grammar == [] or self.changed:
            self.read_input()

        if self.grammar != []:
            self.ui.textBrowser.clear()
            all_symb = []
            all_symb.extend(self.term)
            all_symb.append('$')
            all_symb.extend(self.non_term)
            if 'e' in all_symb:
                all_symb.remove('e')

            head = '{0:12}'.format(' ')
            for X in all_symb:
                head = head + '{0:12}'.format(X)
            self.ui.textBrowser.setText(head+'\n')
            s = '------------'*len(all_symb)
            self.ui.textBrowser.append(s)

            for index, state in enumerate(self.parse_table):
                line = '{0:<12}'.format(index)
                for X in all_symb:
                    if X in state.keys():
                        if X in self.non_term:
                            action = state[X]
                        else:
                            if state[X] > 0:
                                action = 's' + str(state[X])
                            elif state[X] < 0:
                                action = 'r' + str(abs(state[X]))
                            elif state[X] == 0:
                                action = 'accept'
                        
                        line = line + '{0:<12}'.format(action)
                    else:
                        line = line + '{0:<12}'.format("")
    
                self.ui.textBrowser.append(line)
                self.ui.textBrowser.append(s)


    def disp_parsing(self):
        if self.grammar == [] or self.changed:
            self.read_input()
        if self.grammar != []:
            self.ui.textBrowser.clear()
            line_input = self.ui.lineEdit.text()
            self.parse(self.parse_table, self.augment_grammar, line_input)



    def parse(self,parse_table,augment_grammar,inpt):
        inpt = list(inpt+'$')
        stack = [0]
        a = inpt[0]
        try:
            head = '{0:40} {1:40} {2:40}'.format("Stack","Input", "Actions")
            self.ui.textBrowser.setText(head)
            while True:
                string = '\n{0:<40} {1:<40} '.format(stack, ''.join(inpt))
                s = stack[len(stack)-1]
                action = parse_table[s][a]
                if action > 0:
                    inpt.pop(0)
                    stack.append(action)
                    self.ui.textBrowser.append(string + 'Shift ' + a+ '\n')
                    a = inpt[0]
                elif action < 0:
                    prod = augment_grammar[-action]
                    if prod[1] != 'e':
                        for i in prod[1]:
                            stack.pop()
                    t = stack[len(stack)-1]
                    stack.append(parse_table[t][prod[0]])
                    self.ui.textBrowser.append(string + 'Reduce ' + prod[0] + ' -> '+ prod[1] + '\n')
                elif action == 0:
                    self.ui.textBrowser.append('ACCEPT\n')
                    break
        except KeyError:
            self.ui.textBrowser.append('\n\nERROR\n')


    def exit_app(self):
        QtGui.QApplication.quit()
        
    def disp_author(self):
        QtGui.QMessageBox.information(self, "About", "LALR PARSER\n\nAuthor:\n  Hemil Mehta Y S\t", QtGui.QMessageBox.Ok)



if __name__ == '__main__':
    app = QtGui.QApplication(sys.argv)
    myapp = parser()
    myapp.show()
    sys.exit(app.exec())
