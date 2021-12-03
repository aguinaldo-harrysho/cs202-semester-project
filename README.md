# cs202-semester-project

### TODO:
After passing a file through the Reader class, pass the filename to the actual Wav reader (header and body)

### Responsibilites:
Driver & Metadata - Alexander P
UI - Harrumakii

Normalization - MistaHouse
Echo - Dylan Perkins
Gain Adjustment - 


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
      - Read file audio data ❌
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