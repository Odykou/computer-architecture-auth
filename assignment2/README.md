# Αρχιτεκτονική Υπολογιστών   
### Ομάδα 10
#### Κουτσός Οδυσσέας (8659) - Ντινιαρόπουλος Δημήτριος (9345)
![gem5](https://www.gem5.org/assets/img/blog/gem5-linux.png)

### Δεύτερη εργαστηριακή άσκηση
#### ΒΗΜΑ ΠΡΩΤΟ
##### Ερώτημα 1:
-   Τα ζητούμενα μεγέθη για τις L1 και L2 Cache, από το config.ini:
- L1 Instruction cache:
	- Line 833: size=32768	(ή 32kB)
	- Line 816: assoc=2

- L1 Data cache:
	- Line 169: size=65536	(ή 64kB)
	- Line 152: assoc=2

- L2 cache:
	- Line 1078: size=2097152 (ή 2MB)
	- Line 1061: assoc=8

- Cache line size:
	- Line 15: cache_line_size=64 (bytes)

##### Ερώτημα 2:
Από τα αντίστοιχα αρχεία stats.txt για κάθε πρότυπο αρεικρισίας / benchmark, εξάγουμε τα στοιχεία που παρουσιάζονται στα παρακάτω διαγράμματα:
    ![sim_seconds](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment2/charts/sim_seconds.png)
    ![cpi](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment2/charts/cpi.png)
    ![dcache_miss_rate](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment2/charts/dcache_miss_rate.png)
    ![icache_miss_rate](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment2/charts/icache_miss_rate.png)
    ![l2cache_miss_rate](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment2/charts/l2cache_miss_rate.png)
    

##### Ερώτημα 3
Το `system.clk_domain.clock` δηλαδή το ρολόι συγχρονισμού του συστήματος είναι ίδιο και στις δύο περιπτώσεις και ίσο με 1000, δηλαδή 1 GHz. Το ρολόι αυτό ρυθμίζει το ρολόι του συστήματος συμπεριλαμβανομένου του memory controller, του memory bus και του DVFS (Dynamic Voltage and Frequency Scaling) handler.

Το default `system.cpu_clk_domain` δηλαδή το ρολόι χρονισμού της CPU είναι 500 ή 2 GHz, επομένως τώρα τρέχουμε για 1 GHz (και όχι για 2 GHz όπως πριν). Το ρολόι αυτό ρυθμίζει το ρολόι του CPU και των μονάδων επεξεργασίας του, δηλαδή των L1 Data και Instruction cache, της L2 cache and της walk cache.

Αν προσθέσουμε άλλον έναν επεξεργαστή η συχνότητα θα είναι αυτή που δηλώνεται στο αρχείο se.py, δηλαδή 1 GHz για το `system.clk_domain.clock` και 2 GHz για το `system.cpu_clk_domain` , εκτός αν ορίσουμε διαφορετική συχνότητα με τις εντολές `--sys-clock = #` και `--cpu-clock = #` αντίστοιχα.

Τόσο για cpu-clock = 1 GHz όσο και για cpu-clock = 2 GHz παρατηρούμε ότι στα specsjeng και speclibm δεν υπάρχει τέλειο scaling διότι έχουν μεγάλο l2 cache miss rate. Πιο συγκεκριμένα, όποτε συμβαίνει ένα L2 cache miss καθυστερεί η προσπέλαση της RAM μέσω του memory controller και του memory bus.

#### ΒΗΜΑ ΔΕΥΤΕΡΟ
##### Ερώτημα 1
Με βάση το πρώτο μέρος, για τα πρότυπα αρεικρισίας / benchmarks του ερωτήματος 2 επιλέχθηκαν οι ακόλουθες τιμές:
- L1 Data Cache Size: 64 kB, 128 kB
- L1 Instruction Cache Size: 32 kB, 64 kB
- L2 Cache Size: 1 MB, 2 MB, 4 MB
- L1 Data Cache Associativity: 2, 4, 8
- L1 Instruction Cache Associativity: 2, 4, 8
- L2 Cache Associativity: 4, 8
- Cache Line Size: 32 Bytes, 64 Bytes, 128 Bytes 
Για την αυτοματοποιημένη εκτέλεση των εντολών, έγινε χρήση του bash script [run.sh](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment2/Step_2/run.sh) . Παρακάτω βλέπουμε τις δοκιμές για το κάθε benchmark, με τα παραμέτρους της καθεμιάς.

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

##### Ερώτημα 2
Η ανάκτηση των ζητούμενων δεδομένων έγινε με την χρήση του bash script που δώθηκε, το [read_results.sh](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment2/Step_2/read_results.sh), καθώς και του [conf_script.ini](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment2/Step_2/conf_script.ini), που συγκεντρώνουν τα απαραίτητα αποτελέσματα στο [Results.txt](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment2/Step_2/Results.txt). Παραθέτουμε τα εξής διαγράμματα:
- specbzip: Όπως φαίνεται από τα δεδομένα, μια αύξηση του μεγέθους τόσο της L1 dcache όσο και της L2 cache φέρνει μια μικρή αύξηση της απόδοσης (μείωση του CPI). Η αύξηση του associativity, δε φαίνεται να φέρνει ουσιαστική αύξηση της απόδοσης.
![specbzip_cpi](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment2/charts/specbiz_cpi.png)
- specmcf: Το μόνο που επέφερε ουσιαστική αύξηση της απόδοσης ήταν η αύξηση της L1 icache, πράγμα που μείωσε και το miss rate της.
![specmcf_cpi](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment2/charts/specmcf_cpi.png)
- spechmmer: Επειδή η απόδοση παραμένει ουσιαστικά σταθερή και επειδή παρατηρούμε σημαντικό miss rate για την L2, μπορούμε να διατηρήσουμε μικρές σε μέγεθος τις L1d και L2, καθώς και το associativity της L2
![spechmmer_cpi](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment2/charts/spechmmer_cpi.png)
- specsjeng: Το μόνο που επέφερε ουσιαστική αύξηση της απόδοσης ήταν η αύξηση του cache line size.
![specsjeng_cpi](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment2/charts/specsjeng_cpi.png)
- speclibm: Το μόνο που επέφερε ουσιαστική αύξηση της απόδοσης ήταν η αύξηση του cache line size.
![speclibm_cpi](https://github.com/SoreenDesu/computer-architecture-auth/blob/main/assignment2/charts/speclibm_cpi.png)


#### ΒΗΜΑ ΤΡΙΤΟ
Η συνάρτηση κόστους που επιλέξαμε είναι: 
> cost = (L1_dcache_size + L1_icache_size) / kB + L2_cache_size / 32 kB + 
(L1_dcache_assoc + L1_icache_assoc + L2_cache_assoc) * 96 + cache_line_size

- specbzip: Καλύτερη επιλογή βρίσκουμε στο specbzip_0 με χαρακτηριστικά:
  - L1_dcache_size = 64kB
  - L1_icache_size = 32kB
  - L2_cache_size = 1MB
  - L1_dcache_assoc = 2
  - L1_icache_assoc = 2
  - L2_cache_assoc = 4
  - cacheline_size = 64B
 
 Το κόστος υπολογίσθηκε 960 και το κόστος * CPI ισούται με 1636,932 . Όπως είχαμε αναφέρει και στο βήμα 2, η απόδοση δεν αλλάζει σημαντικά επομένως για αυτό το benchmark μπορούμε να χρησιμοποιήσουμε όσο μικρότερες και φθηνότερες παραμέτρους. 

- specmcf: Καλύτερη επιλογή βρίσκουμε στο speccmcf_1 με χαρακτηριστικά:
  - L1_dcache_size = 64kB
  - L1_icache_size = 64kB
  - L2_cache_size = 1MB
  - L1_dcache_assoc = 2
  - L1_icache_assoc = 2
  - L2_cache_assoc = 8 
  - cacheline_size = 64B
 
Το κόστος υπολογίσθηκε 1376 και το κόστος * CPI ισούται με 1581,551 . Εδώ θα χρησιμοποιήσουμε L1_icache = 64kB ή και μεγαλύτερη, και τις υπόλοιπες παραμέτρους θα τις διατηρήσουμε όσο μικρότερες και φθηνότερες γίνεται.

 - spechmmer: Καλύτερη επιλογή βρίσκουμε στο spechmmer_0 με χαρακτηριστικά:
   - L1_dcache_size = 32kB
   - L1_icache_size = 32kB
   - L2_cache_size = 2MB
   - L1_dcache_assoc = 2
   - L1_icache_assoc = 2
   - L2_cache_assoc = 8
   - cacheline_size = 64B
 
Το κόστος υπολογίσθηκε 1344 και το κόστος * CPI ισούται με 1901,368 .Εδώ μπορούμε να χρησιμοποιήσουμε όσο μικρότερες και φθηνότερες παραμέτρους γίνεται. Δεδομένου της συνάρτησης κόστους που χρησιμοποιήσαμε παρατηρούμε ότι δεν αυξάνεται ιδαίτερα το (κόστος*CPI) με αύξηση της L1_dcache. Δεδομένου ότι μειώνει σημαντικά το miss rate της θα μπορούσαμε να τη διατηρήσουμε υψηλά.

- specsjeng: Καλύτερη επιλογή βρίσκουμε στο specjeng_4 με χαρακτηριστικά:
  - L1_dcache_size = 128kB
  - L1_icache_size = 32kB
  - L2_cache_size = 4MB
  - L1_dcache_assoc = 4
  - L1_icache_assoc = 2
  - L2_cache_assoc = 8
  - cacheline_size = 128B

Το κόστος υπολογίσθηκε 1760 και το κόστος * CPI ισούται με 11971,47 .Εδώ διατηρούμε το μέγεθος της cacheline στα 128B ή και περισσότερο και τις υπόλοιπες παραμέτρους σε όσο μικρότερες και φθηνότερες επιλογές υπάρχουν.

- speclibm: Καλύτερη επιλογή βρίσκουμε στο speclibm_4 με χαρακτηριστικά:
  - L1_dcache_size = 128kB
  - L1_icache_size = 32kB
  - L2_cache_size = 4MB
  - L1_dcache_assoc = 4
  - L1_icache_assoc = 2
  - L2_cache_assoc = 8
  - cacheline_size = 128B
 
Το κόστος υπολογίσθηκε 1760 και το κόστος * CPI ισούται με 4535,525 .Εδώ διατηρούμε το μέγεθος της cacheline τουλάχιστον στα 128B και τις υπόλοιπες παραμέτρους σε όσο μικρότερες και φθηνότερες επιλογές υπάρχουν.

#### Κριτική Εργασίας
- Θετικά στοιχεία:
    - Το δεύτερο εργαστήριο, ήταν μία πολύ καλή αφορμή για ενασχόληση με θέματα που καλέιται να αντιμετωπίσει -πρακτικά, και όχι μόνο θεωρητικά- ένας αρχιτέκτονας σύγχρονων επεξεργαστών.
- Προτάσεις 
    - Κάτι που παρατηρείται συχνά, είναι πως ένα απλό copy - paste, μέσα από το pdf του εργαστηρίου δημιουργεί θέματα, πιθανόν λόγω της επιλεγμένης γραμματοσειράς. Θα ήταν καλή μία επισήμανση πως κάτι τέτοιο πρέπει να αποφεύγεται.  
    - Στο πρώτο βήμα, και συγκεκριμένα στο τρίτο ερώτημα, έπρεπε να ζητείται να τρέξουμε --cpu-clock=1 Ghz και όχι 2 GHz, διότι 2 Ghz είναι η default τιμή και όχι αντίστροφα.

