# Αρχιτεκτονική Υπολογιστών   
### Ομάδα 10
#### Κουτσός Οδυσσέας (8659) - Ντινιαρόπουλος Δημήτριος (9345)
![gem5](https://www.gem5.org/assets/img/blog/gem5-linux.png)

### Τρίτη εργαστηριακή άσκηση
#### ΒΗΜΑ ΠΡΩΤΟ
##### Ερώτημα 1:
- Η κατανάλωση ισχύος των κυκλωμάτων CMOS έχει τρία κύρια στοιχεία: dynamic, short-circuit και leakage power. Τα κυκλώματα καταναλώνουν dynamic ισχύ όταν φορτίζουν και εκφορτίζουν τα χωρητικά φορτία για να αλλάξουν καταστάσεις. Η δυναμική ισχύς είναι ανάλογη με τη συνολική χωρητικότητα φορτίου, την τάση τροφοδοσίας, την ταλάντωση της τάσης κατά την αλλαγή καταστάσεων, τη συχνότητα ρολογιού και τον παράγοντα δραστηριότητας.

- Το ρεύμα διαρροής εξαρτάται από το πλάτος των τρανζίστορ και την λογική κατάσταση των συσκευών. Υπάρχουν δύο μηχανισμοί διαρροής. Η διαρροή υποστρώματος εμφανίζεται επειδή ένα μικρό ρεύμα διέρχεται μεταξύ του source και του drain των τρανζίστορ σε κατάσταση off. Η διαρροή πύλης είναι το ρεύμα που διαρρέει μέσω του τερματικού της πύλης και ποικίλλει σημαντικά με την κατάσταση της συσκευής.

- Σε περίπτωση που τρέξουμε δύο διαφορετικά προγράμματα ξεχωριστά, θα επηρεαστεί μόνο η κατανάλωση δυναμικής ισχύος (dynamic power) αφού εξαρτάται από την ταλάντωση της τάσης κατά την αλλαγή καταστάσεων και τον παράγοντα δραστηριότητας. Στο πρόγραμμα που προκαλούνται περισσότερες αλλαγές κατάστασης θα έχουμε και τη μεγαλύτερη κατανάλωση δυναμικής ισχύος.

- Όσο μεγαλύτερη η χρονική διάρκεια εκτέλεσης τόσο μεγαλύτερη η κατανάλωση ενέργειας. Για να επηρεαστεί η ισχύς πρέπει να επηρεαστεί η συχνότητα και οι σχεδιαστικές παράμετροι του επεξεργαστή. Όπως παρατηρούμε, τρέχοντας το McPAT μονάδα των αριθμών κατανάλωσης είναι το Watt και όχι Watt ανά μονάδα χρόνου.

##### Ερώτημα 2:
Ο επεξεργαστής των 40 watt μπορεί να εκτελέσει το πρόγραμμα σε μικρότερο χρόνο, καταναλώνοντας λιγότερη ενέργεια με αποτέλεσμα η διάρκεια λειτουργίας της μπαταρίας να είναι μεγαλύτερη. Όπως αναφέραμε ο McPAT δε μας δίνει αποτελέσματα σχετικά με το χρόνο πάρα μόνο για την κατανάλωση ισχύος. Τα απαραίτητα δεδομένα σχετικά με το χρόνο για τον υπολογισμό της κατανάλωσης ενέργειας μπορούμε να τα πάρουμε με προσομοίωση με το gem5.


##### Ερώτημα 3
Παρατηρούμε ότι ο Xeon έχει `Runtime Dynamic = 72.9199 W` δηλαδή προκειμένου να εκτελέσει ένα πρόγραμμα με χρόνο εκτέλεσης 1 sec καταναλώνει 72.9199 Joules ενώ ο ARM A9 έχει `Runtime Dynamic = 2.96053 W` και αφού είναι 40 φορές πιο αργός από τον Xeon θα καταναλώσει 2.96053 * 40 = 118.4212 Joules προκειμένου να εκτελέσει το ίδιο πρόγραμμα. Επομένως ο ARM A9 θα κατανάλωνε περισσότερη ενέργεια. Αν όμως δεν απενεργοποιηθεί το σύστημα μετά την εκτέλεση της εφαρμογής θα εξακολουθούμε να έχουμε κατανάλωση ισχύος διαρροής. Ο Xeon έχει `Total Leakage = 36.8319 W` ενώ ο ARM A9 έχει `Total Leakage = 0.108687 W`, επομένως από κάποια στιγμή και μετά ο ARM 9 θα καταναλώνει λιγότερη ενέργεια.

#### ΒΗΜΑ ΔΕΥΤΕΡΟ
Αρχικά, παραθέτουμε τις παραμέτρους για το κάθε πρότυπο αρεικρισίας / benchmark του δεύτερου εργαστηρίου:

| Benchmarks   | L1\_dcache\_size | L1\_icache\_size | L2\_cache\_size | L1\_dcache\_assoc | L1\_icache\_assoc | L2\_cache\_assoc | cacheline\_size |
| ------------ | ---------------- | ---------------- | --------------- | ----------------- | ----------------- | ---------------- | --------------- |
| specbzip\_0  | 64               | 32               | 1024            | 2                 | 2                 | 4                | 64              |
| specbzip\_1  | 128              | 32               | 1024            | 2                 | 2                 | 4                | 64              |
| specbzip\_2  | 128              | 32               | 2048            | 2                 | 2                 | 4                | 64              |
| specbzip\_3  | 128              | 32               | 4096            | 2                 | 2                 | 4                | 64              |
| specbzip\_4  | 128              | 32               | 4096            | 4                 | 2                 | 4                | 64              |
| specbzip\_5  | 128              | 32               | 4096            | 8                 | 2                 | 4                | 64              |
| specmcf\_0   | 64               | 32               | 1024            | 2                 | 2                 | 8                | 64              |
| specmcf\_1   | 64               | 64               | 1024            | 2                 | 2                 | 8                | 64              |
| specmcf\_2   | 64               | 64               | 2048            | 2                 | 2                 | 8                | 64              |
| specmcf\_3   | 64               | 64               | 4096            | 2                 | 2                 | 8                | 64              |
| specmcf\_4   | 64               | 64               | 4096            | 2                 | 4                 | 8                | 64              |
| specmcf\_5   | 64               | 64               | 4096            | 2                 | 8                 | 8                | 64              |
| spechmmer\_0 | 32               | 32               | 2048            | 2                 | 2                 | 8                | 64              |
| spechmmer\_1 | 64               | 32               | 2048            | 2                 | 2                 | 8                | 64              |
| spechmmer\_2 | 128              | 32               | 2048            | 2                 | 2                 | 8                | 64              |
| spechmmer\_3 | 128              | 32               | 2048            | 4                 | 2                 | 8                | 64              |
| spechmmer\_4 | 128              | 32               | 2048            | 8                 | 2                 | 8                | 64              |
| spechmmer\_5 | 128              | 32               | 2048            | 8                 | 2                 | 8                | 32              |
| specsjeng\_0 | 64               | 32               | 2048            | 2                 | 2                 | 8                | 64              |
| specsjeng\_1 | 128              | 32               | 2048            | 2                 | 2                 | 8                | 64              |
| specsjeng\_2 | 128              | 32               | 4096            | 2                 | 2                 | 8                | 64              |
| specsjeng\_3 | 128              | 32               | 4096            | 4                 | 2                 | 8                | 64              |
| specsjeng\_4 | 128              | 32               | 4096            | 4                 | 2                 | 8                | 128             |
| speclibm\_0  | 64               | 32               | 2048            | 2                 | 2                 | 8                | 64              |
| speclibm\_1  | 128              | 32               | 2048            | 2                 | 2                 | 8                | 64              |
| speclibm\_2  | 128              | 32               | 4096            | 2                 | 2                 | 8                | 64              |
| speclibm\_3  | 128              | 32               | 4096            | 4                 | 2                 | 8                | 64              |
| speclibm\_4  | 128              | 32               | 4096            | 4                 | 2                 | 8                | 128             |

Αρχικά έγινε μετατροπή των απαραίτητων δεδομένων του gem5, σε μορφή συμβατή με τον McPAT, με την χρήση του [GEM5toMcPAT.py](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment3/GEM5toMcPAT.py) και του bash script [GEM5toMcPAT.sh](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment3/bash%20scripts/gem5toMcPAT.sh), και αποθήκευσή τους στον φάκελο [GEM5toMcPAT_results](https://github.com/SoreenDesu/computer-architecture-auth/tree/main/assignment3/gem5toMcPAT_results).
Έπειτα εκτελούμε το bash script [runMcPAT.sh](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment3/bash%20scripts/runMcPAT.sh) για εξαγωγή των ζητούμενων τιμών ισχύος, με είσοδο τα προαναφερθέντα αρχεία. Τα αρχεία αυτά αποθηκεύονται στον φάκελο [McPAT_results](https://github.com/SoreenDesu/computer-architecture-auth/tree/main/assignment3/McPAT_results).
Τέλος, τρέχουμε το bash script [print_energy.sh](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment3/bash%20scripts/print_energy.sh) για αποκόμιση των τελικών τιμών, που αποθηκεύονται στον φάκελο [final_results](https://github.com/SoreenDesu/computer-architecture-auth/tree/main/assignment3/final_results).

Παρουσιάζουμε τα αποτελέσματα στα ακόλουθα διαγράμματα:
- specbzip: Παρατηρούμε ότι η αύξηση του associativity της L1 dcache προκαλεί σημαντική μείωση της καταναλισκόμενης ενέργειας και κατά συνέπεια σημαντική μείωση του EDP. Επομένως, θα διατηρήσουμε το associativity της L1 dcache όσο μεγαλύτερο γίνεται, ενώ τις υπόλοιπες παραμέτρους όσο μικρότερες και φθηνότερες γίνεται.
![specbzip_pp](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment3/charts/specbzip_pp.png)
![specbzip_edp](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment3/charts/specbzip_edp.png)
- spechmmer: Εδώ παρατηρούμε ότι αύξηση του associativity της L1 dcache και μείωση του cacheline size προκαλούν αύξηση της απόδοσης. Θα αυξήσουμε το associativity της L1 dcache και τις υπόλοιπες παραμέτρους όσο μικρότερες και φθηνότερες γίνεται.
![spechmmer_pp](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment3/charts/spechmmer_pp.png)
![spechmmer_edp](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment3/charts/spechmmer_edp.png)
- speclibm: Εδώ θα αυξήσουμε το cacheline size και το associativity της L1 dcache, ενώ τις υπόλοιπες παραμέτρους θα τις διατηρήσουμε όσο μικρότερες και φθηνότερες γίνεται.
![speclibm_pp](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment3/charts/speclibm_pp.png)
![speclbm_edp](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment3/charts/speclibm_edp.png)
- specmcf: Εδώ διατηρούμε το associativity της L1 icache στην τιμή 4 και τις υπόλοιπες παραμέτρους όσο μικρότερες και φθηνότερες γίνεται.
![specmcf_pp](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment3/charts/specmcf_pp.png)
![specmcf_edp](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment3/charts/specmcf_edp.png)
- specsjeng: Εδώ θα αυξήσουμε το cacheline size και το associativity της L1 dcache, ενώ τις υπόλοιπες παραμέτρους θα τις διατηρήσουμε όσο μικρότερες και φθηνότερες γίνεται.
![specsjeng_pp](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment3/charts/specsjeng_pp.png)
![specsjeng_edp](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment3/charts/specsjeng_edp.png)

Τα αποτελέσματα του McPAT μπορεί να παρουσιάζουν σημαντικό σφάλμα είτε γιατί τα μοντέλα του δεν είναι πλήρη, είτε γιατί είναι πολύ υψηλού επιπέδου και δε λαμβάνουν υπόψη στοιχεία ελέγχου χαμηλής λογικής, είτε γιατί αντιπροσωπεύουν εφαρμογές διαφόρων δομών που διαφέρουν από αυτή του πυρήνα που έχουμε στη διάθεσή μας. Επιπλέον, ο McPAT δεν υπολογίζει την έξτρα ισχύ που απαιτείται λόγω miss στις cache. Επομένως, η χρήση  δύο  διαφορετικών  προγραμμάτων  για  την  εκτίμηση  διαφορετικών  πτυχών  του  ίδιου συστήματος θα μπορούσε να είναι πηγή επιπλέον σφαλμάτων εξαιτίας του διαφορετικού miss rate στην κάθε περίπτωση.

#### Κριτική Εργασίας
- Θετικά στοιχεία:
    - Μέσω του τρίτου εργαστηρίου ήμασταν σε θέση να αντιληφθούμε την επιρροή της κατανάλωσης ισχύος και ενέργειας στην απόδοση ενός επεξεργαστή.
- Προτάσεις 
    - Σε γενικές γραμμές, το εργαστήριο μεταφέρει πληθώρα γνώσεων στον φοιτητή. Όμως, σε αρκετά ερωτήματα, τα πολλά συνεχόμενα benchmarks, καταλήγουν να είναι εξαιρετικά μεγάλα σε διάρκεια. Σίγουρα είναι αναγκαία η εκτέλεση μερικών προσωμοιώσεων για εξοικείωση, αλλά σε μεγάλη έκταση, δεν πιστεύουμε πως έχει ιδιαίτερο διδακτικό νόημα. Αντιθέτως, θεωρούμε πως η μελέτη σε ήδη υπάρχοντα δεδομένα που θα δίνονται σε κάθε εργαστηριακή άσκηση, αποτελεί μία καλύτερη τακτική για την επίτευξη των στόχων της κάθε άσκησης. Επίσης, θα υπάρχει ένα κοινό μέτρο σύγκρισης μεταξύ των εργασιών των διαφόρων ομάδων.

###### Πηγές - Βιβλιογραφία: 
- [McPAT: An Integrated Power, Area, and Timing ModelingFramework for Multicore and Manycore Architectures](https://www.hpl.hp.com/research/mcpat/micro09.pdf)
- [Quantifying Sources of Error in McPAT and Potential Impacts on Architectural Studies](https://www.samxi.org/papers/xi_hpca2015.pdf)
