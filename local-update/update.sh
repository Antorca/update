#!/bin/sh

zenity --question \
  --width="380" --height="120" \
  --title="Antorca Upgrade" \
  --text="Antorca will check for system updates! Some checks on your system will be performed. Proceed?"

case $? in
    # NO
    1)
        exit 1
        ;;
    # YES
    0)
        (git clone https://github.com/Antorca/update.git /usr/share/antorca-update/update) | zenity --progress --title="Antorca Upgrade" \
          --text="Getting upgrade tools from the update repository..." \
          --percentage=0 --pulsate --auto-close --width="380" --height="120"
        case $? in
            # CANCEL
            1)
                echo "Upgrade cancelled"
                exit 1
                ;;
        esac
        if [ ! -d "/usr/share/antorca-update/update" ]; then
            zenity --error --title="Antorca Upgrade" --text="Error! Could not download update tools!" --width="380" --height="120"
        else
            zenity --info --title="Antorca Upgrade" --text="Successfully downloaded update tools!" --width="380" --height="120"
        fi
        ;;
esac
