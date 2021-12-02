# cs202-semester-project

Driver & Metadata - Dylan Perkins
Echo - Alexander P
Gain - Harrumakii
Normalization - MistaHouse

Program Flow:
    Start: Present start menu
    If user selects quit, exit program
    Else
    Request filename from user
    Open file specified by filename
    If file does not exist or file is not wav file
        display error message and goto start
    else
        read file metadata
    (1) display metadata to user
        present user with processor menu
        If user selects processor option
        request output filename
        run processor
        save file
        goto Start