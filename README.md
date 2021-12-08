# Basic Level CS202 Semester Project

### Group Members:
-Alexander P
-Harry Sho K Aguinaldo
-Dylan Perkins
-Kyle House

### Responsibilites:
Driver & Metadata - Alexander P
UI - Harry Aguinaldo
Normalization - Kyle House
Echo - Dylan Perkins
Gain Adjustment - Harry Aguinaldo

### Challenges of This Project
Two main challenges we encountered during this project were dealing with file reading/writing and team organization. For some of us, this project was not only our first experience in dealing with binary and special file formats, but this was also our first experience in collaborating with multiple people on one project, all on one github repository. To avoid overwriting each other's work, we had to exercise caution when committing changes to the repository, which required close communication. Additionally, it was also challenging to divide the work into individual tasks for each person. In fact, we had to completely overhaul our approach to dividing the work after our first plan proved to be impractical, since it was difficult to work on the processors before file reading was working. Indeed, the biggest lesson to learn from this project is the value of foresight and proper planning/management; the project may have gone much more smoothly if we had taken a more structured approach to organizing our workflow.

### TODO:
wav_body.h, a struct that holds data for the actual audio in vectors. Will likely extend wav_header.

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
