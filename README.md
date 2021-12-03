# cs202-semester-project

The Wav class in wav.h should be static, no need to initialize.
Pass a file into a method of the Wav class to first determine if it can be opened
read_file
If ture, read the header and determine if it is a WAV file
read_header
returns a wav_header type, a different class is responsible for determining is things remain true througout this processs


Driver & Metadata - Dylan Perkins
Echo - Alexander P
Gain - Harrumakii
Normalization - MistaHouse

Program Flow:
   - Start: Present start menu
   - If user selects quit, exit program
   - Else
   - Request filename from user
   - Open file specified by filename
   - If file does not exist or file is not wav file
     - Display error message and goto start
   - else
     - read file metadata
   - (1) display metadata to user
     -  present user with processor menu
     -  If user selects processor option
     -  request output filename
     -  run processor
     -  save file
     -  goto Start