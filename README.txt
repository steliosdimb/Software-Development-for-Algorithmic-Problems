PROJECT
ΕΡΓΑΣΙΑ 1
Πολυγωνοποίηση Σημειοσυνόλων
ΣΤΕΛΙΟΣ ΔΗΜΗΤΡΙΑΔΗΣ sdi1900050
ΠΑΝΑΓΙΩΤΗΣ ΚΟΝΤΟΕΙΔΗΣ 
Η εργασια αυτη εχει ως στοχο την πολυγωνοποίηση σημειων στον χώρο με δυο διαφορετικους αλγορίθμους τον αυξητικο και τον αλγοριθμο που βασιζεται στο ΚΠ.
Βρισκει ενα πολυγωνο για χ σημεια διαλέγοντας καθε φορα τυχαια ακμη,ή ακμη που δημιουργει πολύγωνο με ελάχιστο εμβαδό,ή ακμη που δημιουργει πολύγωνο με μέγιστο εμβαδο.
Στον αυξητικο αλγόριθμο υπαρχει η επιλογη να τακινομηθουν τα στοιχεία με αυξουσα φθινουσα σειρα ως προς χ,η αντίστοιχα ως προς y.
Aρχεία που περιλαμβάνονται.
Polygon_functions.cpp
Polygon_functions.hpp
PROJECT.cpp
include
CMakeLists.txt
.git
README
Οδηγίες μεταγλώττισης του προγράμματος.
1.cmake -DCGAL_DIR=$CMAKE_INSTALLED_PREFIX/lib/CGAL -DCMAKE_BUILD_TYPE=Release .
2.make
3../PROJECT -i input.txt -o output.txt -algorithm (choose incremental or convex_hull) -edge selection (choose 1 2 3 1=random 2=min 3=max) (this option exists if you choose incremental algorithm)-initialization (choose 1a 1b 2a 2b 
1a=sort by x in increasing order,1b=sort by x in decreasing order,2a sort by y in increasing order,2b sort by y in decreasing order)



