
m = s = 1
GRAVITY = 9.81*m/s 

class Bead:
    def __init__(self, row, height):
        self.row = row
        self.height = height
        self.velocity = 0
        self.touching_ground = False

    def fall(self):
        if not self.touching_ground:
            self.velocity += GRAVITY
            self.height -= self.velocity

    def stop(self):
        if not self.touching_ground:
            self.touching_ground = True
           

def convtoBead(list_of_numbers):
    
    beads = []
    number_number = 0 
    for number in list_of_numbers:
        for i in range(number):
            beads.append(Bead(i, number_number))
        number_number += 1

    return beads

def beaddrop(beads): 
    bead_number = 0
    still_going = True
    while still_going: 
        still_going = False
        for bead in beads:
            if bead.touching_ground == False:
                still_going = True 

        for bead in beads:
            if not bead.touching_ground:
                stp_after = False
                for collbead in beads:
                    if bead.row == collbead.row and collbead.touching_ground:
                       
                        if bead.height < collbead.height + 1:
                            bead.height = collbead.height + 1
                            stp_after = True
                if bead.height <= 0:
                    bead.height = 0
                    bead.stop()
                if stp_after:
                    bead.stop()
                bead.fall()
        bead_number += 1
    return beads

def beadCount(beads, list_of_numbers):
  
    sorted_list = [] 
    for i in range(len(list_of_numbers)):
        sorted_list.append(0) 
    for bead in beads:
        sorted_list[bead.height] += 1 
    return sorted_list 

def sortbead(list_of_numbers):
    res = convtoBead(list_of_numbers)
    res = beaddrop(res)
    res = beadCount(res, list_of_numbers)
    return res

list_of_numbers = [8, 56, 10, 0, 7, 100, 3, 2, 5, 1,9] 
print(sortbead(list_of_numbers))