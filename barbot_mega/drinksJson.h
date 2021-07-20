
const char* drinkJsonStr = "{\
\"drinks\": [\
{\
\"name\": \"Amaretto Sour\",\
\"extras\": \"egg white, 2 dashes Angostura bitters\",\
\"bourbonOz\": 0.5,\
\"ginOz\": 1,\
\"lemonOz\": 1\
},\
{\
\"name\": \"Kentucky Mule\",\
\"extras\": \"\",\
\"bourbonOz\": 2,\
\"limeOz\": 0.5,\
\"gingerBeerOz\": 4\
},\
{\
\"name\": \"Old Fashioned \",\
\"extras\": \"2 dash Angostura bitters and Orange peel\",\
\"bourbonOz\": 2,\
\"simpleOz\": 0.1666\
},\
{\
\"name\": \"Bourbon Sour\",\
\"extras\": \"egg white\",\
\"bourbonOz\": 2,\
\"simpleOz\": 0.1666,\
\"lemonOz\": 0.75\
},\
{\
\"name\": \"Margarita\",\
\"extras\": \"\",\
\"tequilaOz\": 2,\
\"tripleSecOz\": 1,\
\"limeOz\": 1\
},\
{\
\"name\": \"Blue Margarita\",\
\"extras\": \"\",\
\"tequilaOz\": 2,\
\"tripleSecOz\": 1,\
\"blueCurOz\": 1,\
\"limeOz\": 1\
},\
{\
\"name\": \"Tequila Sunrise\",\
\"extras\": \"\",\
\"tequilaOz\": 1.5,\
\"orangeOz\": 6,\
\"grenadineOz\": 0.75\
},\
{\
\"name\": \"Siesta\",\
\"extras\": \"\",\
\"tequilaOz\": 1,\
\"orangeOz\": 0.5,\
\"limeOz\": 0.5,\
\"simpleOz\": 0.5,\
\"campariOz\": 0.5\
},\
{\
\"name\": \"Mexican Mule\",\
\"extras\": \"\",\
\"tequilaOz\": 2,\
\"gingerBeerOz\": 4,\
\"limeOz\": 0.5\
},\
{\
\"name\": \"Orange Paloma\",\
\"extras\": \"\",\
\"tequilaOz\": 1.5,\
\"orangeOz\": 1,\
\"limeOz\": 0.5\
},\
{\
\"name\": \"Mojito\",\
\"extras\": \"mint leaves\",\
\"rumOz\": 2,\
\"simpleOz\": 0.5,\
\"limeOz\": 0.75\
},\
{\
\"name\": \"Daquiri\",\
\"extras\": \"\",\
\"rumOz\": 2,\
\"simpleOz\": 1,\
\"limeOz\": 1\
},\
{\
\"name\": \"Vodka Gimlet\",\
\"extras\": \"\",\
\"vodkaOz\": 2,\
\"simpleOz\": 0.75,\
\"limeOz\": 0.75\
},\
{\
\"name\": \"Cosmo\",\
\"extras\": \"\",\
\"vodkaOz\": 1.5,\
\"tripleSecOz\": 1,\
\"limeOz\": 0.5,\
\"cranOz\": 0.25\
},\
{\
\"name\": \"Moscow Mule\",\
\"extras\": \"\",\
\"gingerBeerOz\": 5,\
\"tripleSecOz\": 1,\
\"limeOz\": 0.5\
},\
{\
\"name\": \"Double Strike\",\
\"extras\": \"\",\
\"vodkaOz\": 1.5,\
\"blueCurOz\": 1,\
\"limeOz\": 0.375,\
\"cranOz\": 0.75\
},\
{\
\"name\": \"Vodka Cran\",\
\"extras\": \"\",\
\"vodkaOz\": 1,\
\"orangeOz\": 0.2,\
\"limeOz\": 0.2,\
\"cranOz\": 4.5\
},\
{\
\"name\": \"Lemon Drop Martini\",\
\"extras\": \"\",\
\"vodkaOz\": 1,\
\"tripleSecOz\": 0.5,\
\"lemonOz\": 0.75,\
\"simpleOz\": 0.25\
},\
{\
\"name\": \"Kamikaze\",\
\"extras\": \"\",\
\"vodkaOz\": 0.75,\
\"tripleSecOz\": 0.75,\
\"limeOz\": 0.75\
},\
{\
\"name\": \"Screwdriver\",\
\"extras\": \"\",\
\"vodkaOz\": 1.5,\
\"orangeOz\": 4\
},\
{\
\"name\": \"Blue Monday\",\
\"extras\": \"\",\
\"vodkaOz\": 1.5,\
\"tripleSecOz\": 0.5,\
\"blueCurOz\": 0.25\
},\
{\
\"name\": \"Cranberry Kiss\",\
\"extras\": \"\",\
\"vodkaOz\": 1,\
\"amarettoOz\": 0.5,\
\"orangeOz\": 0.1875,\
\"cranOz\": 2\
},\
{\
\"name\": \"Gin Gimlet\",\
\"extras\": \"\",\
\"ginOz\": 2,\
\"simpleOz\": 0.75,\
\"limeOz\": 0.75\
},\
{\
\"name\": \"Tom Collins\",\
\"extras\": \"maraschino cherry\",\
\"ginOz\": 2,\
\"lemonOz\": 1,\
\"simpleOz\": 0.5,\
\"seltzerOz\": 1\
},\
{\
\"name\": \"Southside\",\
\"extras\": \"mint leaves\",\
\"ginOz\": 2,\
\"lemonOz\": 1,\
\"limeOz\": 0.5,\
\"simpleOz\": 0.5\
},\
{\
\"name\": \"Bluebird\",\
\"extras\": \"2 dashes bitters\",\
\"ginOz\": 2,\
\"tripleSecOz\": 1,\
\"blueCurOz\": 1\
},\
{\
\"name\": \"Mudslide\",\
\"extras\": \"1.5 oz cream\",\
\"vodkaOz\": 1,\
\"kahluaOz\": 1,\
\"baileysOz\": 1.5\
},\
{\
\"name\": \"White Russian\",\
\"extras\": \"1 oz cream\",\
\"vodkaOz\": 2,\
\"kahluaOz\": 1\
},\
{\
\"name\": \"Irish Cactus\",\
\"extras\": \"\",\
\"baileysOz\": 2,\
\"tequilaOz\": 1\
},\
{\
\"name\": \"Espresso Martini\",\
\"extras\": \"1 oz coffee\",\
\"vodkaOz\": 2,\
\"kahluaOz\": 0.75\
},\
{\
\"name\": \"Sugar Cookie Martini\",\
\"extras\": \"\",\
\"tequilaOz\": 1.5,\
\"amarettoOz\": 1,\
\"baileysOz\": 1.5\
},\
{\
\"name\": \"Girl Scout Cookie\",\
\"extras\": \"\",\
\"kahluaOz\": 1,\
\"baileysOz\": 1,\
\"peppermintShOz\": 1\
},\
{\
\"name\": \"Mind Eraser\",\
\"extras\": \"\",\
\"vodkaOz\": 1.5,\
\"kahluaOz\": 1.5,\
\"seltzerOz\": 1.5\
},\
{\
\"name\": \"Toasted Almond\",\
\"extras\": \"2 oz cream\",\
\"kahluaOz\": 1,\
\"amarettoOz\": 1\
},\
{\
\"name\": \"Italian Sunset\",\
\"extras\": \"\",\
\"amarettoOz\": 2,\
\"orangeOz\": 3,\
\"seltzerOz\": 3,\
\"grenadineOz\": 0.1\
},\
{\
\"name\": \"Blue Hawaiian\",\
\"extras\": \"\",\
\"pineappleOz\": 3,\
\"vodkaOz\": 0.75,\
\"rumOz\": 0.75,\
\"blueCurOz\": 0.5,\
\"limeOz\": 0.5,\
\"lemonOz\": 0.5\
},\
{\
\"name\": \"Sex on the Beach\",\
\"extras\": \"\",\
\"vodkaOz\": 2,\
\"peachShOz\": 1,\
\"orangeOz\": 2,\
\"cranOz\": 2\
},\
{\
\"name\": \"Jungle Bird\",\
\"extras\": \"\",\
\"rumOz\": 1.5,\
\"campariOz\": 0.75,\
\"pineappleOz\": 1.5,\
\"limeOz\": 0.5,\
\"simpleOz\": 0.5\
}\
]\
} ";
