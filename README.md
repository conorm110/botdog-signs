# botdog-signs
 large 7 segment display using an ARGB light strip and an arduino


Short presses (< 1 second ish) increments the number. Long presses (> 2 seconds ish) increments the color. There are red, green, yellow, and blue color options.


There are four seven segment signs. Because each sign has slightly different strip lengths (I struggled with counting when I made them) **there is an int on line 52 that needs to be set before uploading code to the boards.** Each sign has a number written on the back between zero and three corresponding to this int.


Each sign needs to be driven by a power supply between 6 and 12 volts -- USB power supplies (even in parallel or series or some combination) will not work. Some batteries that work:
- Milwaukee M12 Drill Batteries (work super well, we just shoved the power wires into the holes on the battery and it lasted all weekend -- maybe think of a safer way to do this)
- [These on amazon](https://www.amazon.com/TalentCell-Rechargeable-Amplifier-Multi-led-Indicator/dp/B00MHNQIR2/ref=sr_1_54?crid=2IUPXO9CWQ789&dib=eyJ2IjoiMSJ9.r1BQaRm3E89cQI7KMoRyLvfnyDNTPWwh6gobXQyKaUFTEXX2OPQcFOzBo159ln5kSFzkF98wzBRqTYDa4IqgWMnaRlNRfAVI5G7azyWi8lY.miMZrscxgHPJ7H7UMZRiNmZU-6FAlgz8BNeqQHCoR6g&dib_tag=se&keywords=12v+battery&qid=1716403721&sprefix=12v+batte%2Caps%2C96&sr=8-54) cost a bit but would be super easy to use

Also all the boards are slightly different but they all do the exact same thing. They either have an arduino nano or an arduino uno and a dc-dc buck converter or a linear regulator for power.


