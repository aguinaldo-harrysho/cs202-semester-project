# cs202-semester-project

### TODO:
wav_body.h, a struct that holds data for the actual audio in vectors. Will likely extend wav_header.

### Group Members:
-Alexander P
-Harry Sho K Aguinaldo
-Dylan Perkins
-MistaHouse

### Responsibilites:
Driver & Metadata - Alexander P
UI - Harry Aguinaldo
Normalization - MistaHouse
Echo - Dylan Perkins
Gain Adjustment - Harry Aguinaldo


## Program Flow:
   1. Start: Present start menu ✔️
      - If user selects quit, exit program ✔️
   2. Else ✔️
      - Request filename from user ❗ (Disabled for testing)
      - Open file specified by filename ✔️
        - If file does not exist or file is not wav file ✔️
        - Display error message and goto start ✔️
   3. Otherwise ✔️
      - Read file metadata ✔️
      - Read file audio data ✔️
   4. Display metadata to user * ✔️
      - Present user with processor menu ✔️
      - If user selects processor option
      - Request output filename
      - Run processor
      - Save file
      - Goto Start

(*) In order:
1. Filename
2. Sample rate
3. Bits per sample
4. Stereo or mono