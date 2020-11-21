# Αρχιτεκτονική Υπολογιστών   
### Ομάδα 10
#### Κουτσός Οδυσσέας (8659) - Ντινιαρόπουλος Δημήτριος (9345)
![gem5](https://www.gem5.org/assets/img/blog/gem5-linux.png)

### Πρώτη εργαστηριακή άσκηση
##### Ερώτημα 1:
- Βασικές παράμετροι για την εξομοίωση, από το starter_se.py:
    - Τύπος CPU: AtomicSimpleCPU, MinorCPU, HPI
    - `voltage_domain = 3.3V`
    - `clk_domain = 1GHz`
    - `cpu.cluster.voltage_domain = 1.2V`
    - `cpu.cluster.clk_domain = 4GHz`
    - `mem_mode = timing`
    - `mem-size default = 2Gb`
    - `membus = SystemXBar()`
    - `num-cores default = 1`

##### Ερώτημα 2:
1. Μετά από αναζήτηση στο αρχείο [Task 1 and 2/config.ini](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment1/Task%201%20and%202/config.ini) μπορούμε να επιβεβαιώσουμε τα παρακάτω χαρακτηριστικά
    - Line 65: `type = MinorCPU`
    - Line 1652: `voltage = 3.3V`
    - Line 44: `clock = 1000`, δηλαδή 1/1000 ticks = 1/[10^(-9)] = 1GHz
    - Line 1339: `voltage = 1.2 V`
    - Line 58: `clock = 250`, δηλαδή 1/250ticks = 4/[10^(-9)] = 4GHz
    - Line 20: `mem_mode = timing`
    - Line 1610: `type = CoherentXBar`
    - Line 113: `numThreads = 1`
2. Ανατρέχοντας στο αρχείο [Task 1 and 2/stats.txt](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment1/Task%201%20and%202/stats.txt) εντοπίζουμε στην γραμμή 715 πως ο αριθμός των commited εντολών, ή αλλιώς 'commited lines' είναι 479, για read and write.

##### Ερώτημα 3
In-Order μοντέλα CPU, των οποίων κάνει χρήση ο gem5:
- AtomicSimpleCPU:
Αυτό το μοντέλο χρησιμοποιεί Atomic memory access δηλαδή εκπληρώνει ένα transaction σε ένα μόνο κάλεσμα συνάρτησης. Αυτός ο τύπος memory access μοντελοποιεί τις αλλαγές κατάστασης και υπολογίζει τον κατά προσέγγιση λανθάνοντα χρόνο γρήγορα, χωρίς καθυστερήσεις, πράγμα που το καθιστά κατάλληλο για loosely timed προσομοιώσεις (fast-forwarding) ή cache warming. Έτσι, ο AtomicSimpleCPU εκτελεί όλες τις λειτουργίες για μια εντολή σε κάθε CPU tick() και μπορεί να πάρει μια γενική εκτίμηση του συνολικού χρόνου προσπέλασης στην cache υπολογίζοντας το latency από τις atomic προσπελάσεις.
- TimingSimpleCPU:
Αυτό το μοντέλο χρησιμοποιεί Timing memory access. Αυτό σημαίνει ότι περιμένει μέχρι να επιστρέψει η προσπέλαση στη μνήμη πριν συνεχίσει. Παρόλα αυτά το TimingSimpleCPU είναι επίσης ένα fast-to-run μοντέλο, δεδομένου ότι απλοποιεί ορισμένες πτυχές όπως το pipelining, πράγμα που σημαίνει ότι μόνο μία εντολή επεξεργάζεται κάθε στιγμή. Κάθε αριθμητική εντολή εκτελείται από το TimingSimpleCPU σε έναν μόνο κύκλο, ενώ οι προσπελάσεις στη μνήμη απαιτούν πολλαπλούς κύκλους.
 - MinorCPU:
Το μοντέλο αυτό αποτελεί ένα ευέλικτο μοντέλο in-order CPU που αναπτύχθηκε αρχικά για να υποστηρίζει το Arm ISA, ενώ υποστηρίζει και άλλα ISAs. Το MinorCPU έχει fixed four-stage in-order execution pipeline, ενώ διαθέτει ρυθμιζόμενες δομές δεδομένων και συμπεριφορά εκτέλεσης. Επομένως μπορεί να ρυθμιστεί σε επίπεδο μικρο-αρχιτεκτονικής για να μοντελοποιήσει συγκεκριμένο επεξεργαστή. Το four-stage pipeline περιλαμβάνει fetching lines, decomposition into macro-ops,  decomposition of macro-ops into micro-ops και execute.
- High-Performance In-order (HPI) CPU:
Το μοντέλο αυτό είναι βασισμένο στην αρχιτεκτονική Arm και το ονομάζουμε HPI. To HPI CPU timing model ρυθμίζεται για να αντιπροσωπεύει μια μοντέρνα in-order Armv8-A εφαρμογή. Το pipeline του HPI CPU χρησιμοποιεί το ίδιο four-stage μοντέλο όπως ο MinorCPU που αναφέραμε προηγουμένως.

1. Σημείωνουμε πως για τους σκοπούς των παρακάτω υποερωτημάτων έγινε χρήση ενός απλού προγράμματος C, το οποίο υπολογίζει και εμφανίζει τους δέκα πρώτους αριθμούς.  
    - MinorCPU
      Line 12:	`sim_seconds	0.000057	# Number of seconds simulated`
    - TimingSimpleCPU
      Line 12:	`sim_seconds	0.000083	# Number of seconds simulated`
2. Ο χρόνος στην περίπτωση του TimingSimpleCPU είναι μεγαλύτερος από την περίπτωση του MinorCPU. Αυτό συμβαίνει διότι στην περίπτωση του TimingSimpleCPU περιμένει την προσπέλαση μνήμης να τελειώσει πριν συνεχίσει ενώ δεν υποστηρίζει pipeline. Από την άλλη, το MinorCPU έχει pipeline τεσσάρων σταδίων. Επίσης, παρατηρούμε ότι οι κύκλοι που προσομοιώθηκαν στην περίπτωση του MinorCPU είναι 113218 ενώ στον TimingSimpleCPU είναι 165590. Αυτό συμβαίνει γιατί όπως αναφέραμε στην περίπτωση του Timing memory access απαιτούνται πολλαπλοί κύκλοι.
3. Πρώτα κάνουμε προσομείωση με συχνότητα 500MHz με την εντολή `--sys-clock=500000000`
    - MinorCPU
      Line 12:	`sim_seconds	0.000064	# Number of seconds simulated`
    - TimingSimpleCPU
      Line 12:	`sim_seconds	0.000089	# Number of seconds simulated`
 Όπως βλέπουμε οι χρόνοι εκτέλεσης αυξήθηκαν πράγμα λογικό αφού μειώσαμε τη συχνότητα από 1GHz που ήταν προηγουμένως.  
Τώρα αλλάζουμε τη τεχνολογία της μνήμης σε DDR3_2133_8x8 με την εντολή `--mem-type=DDR3_2133_8x8`
    - MinorCPU
     Line 12:	`sim_seconds	0.000055	# Number of seconds simulated`
    - TimingSimpleCPU
     Line 12:	`sim_seconds	0.000082	# Number of seconds simulated`
  
  Παρατηρούμε ότι μειώθηκαν οι χρόνοι εκτέλεσης από την αρχική μας περίπτωση. Αυτό είναι λογικό αφού αρχικά είχαμε DDR3_1600_8x8 : (1.6 x 8 x 8 / 8 = 12.8 GBps) και τώρα DDR3_2133_8x8 : (2.133 x 8 x 8 / 8 = 17.0 GBps).

#### Κριτική Εργασίας
- Θετικά στοιχεία:
    - Η υλοποίηση της εργασίας, έχει ως αποτέλεσμα 'hands-on' εξοικείωση με τα εργαλεία git και Markdown, τα οποία δεν έχουν χρησιμοποιηθεί ιδιαίτερα ως τώρα σε κάποιο προηγούμενο μάθημα παρά το γεγονός ότι είναι εξαιρετικά χρήσιμα και απλά στην χρήση.
    - Επίσης, το ίδιο το terminal, ή ακόμα και το ίδιο το λειτουργικό Linux, είναι πράγματα τα οποία πολλοί φοιτητές δεν έχουν ακόμα ιδιαίτερη ευχαίρεια στο να τα χρησιμοποιούν. Η εργασία αυτή, μεριμνά στο να υπάρξει μία "γνωριμία" με το συγκεκριμένο λειτουργικό και τα εργαλεία τα οποία προσφέρει.
    - Τέλος, αποτέλεσε την αφορμή, για περαιτέρω ενασχόληση με την λειτουργία της αρχιτεκτονικής ARM και των in order CPU που υποστηρίζει ο gem5.
- Αρνητικά στοιχεία:
    - Στο υποερώτημα 3α, εντοπίσθηκε λάθος στην δοσμένη εντολή, που οδηγούσε στην εμφάνιση του αντίστοιχου σφάλματος στο terminal. Συγκεκριμένα η εντολή που χρησιμοποιήσαμε είναι:
      > $ ./build/ARM/gem5.opt configs/example/se.py --cpu=MinorCPU --caches -c
tests/test-progs/hello/bin/arm/linux/hello

    - Κατά την εγκατάσταση των προαπαιτούμενων πακέτων, προέκυψε μία σειρά από σφάλματα, των οποίων η διόρθωση κατέστησε την όλη εγκατάσταση εξαιρετικά χρονοβόρα. Η μη εξοικείωση με το terminal και το λειτουργικό Linux, μπορεί να αποθαρρύνει κάποιον φοιτητή.
- Προτάσεις 
    - Η παροχή ενός "Image" για το Virtual Machine με προεγκατεστημένα όλα τα προαπαιτούμενα προγράμματα, πακέτα, κτλ. για την χρήση του gem5, θα μείωνε τον χρόνο που χρειάζεται για την αποσφαλμάτωση των προβλημάτων που παρουσιάζονται.  


###### Πηγές - Βιβλιογραφία: 
- [gem5.org](https://www.gem5.org/ "gem5 Official Website")
- [Arm Research Starter Kit: System Modeling using gem5 by Ashkan Tousi and Chuan Zhu
July 2017 (updated October 2020)](https://raw.githubusercontent.com/arm-university/arm-gem5-rsk/master/gem5_rsk.pdf)


