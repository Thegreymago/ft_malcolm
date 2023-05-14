#!/bin/bash

filepath="$1"

if [ -z "$filepath" ]; then
  echo "Aucun fichier spécifié."
  exit 1
fi

filename=$(basename "$filepath")
filetype=$(file -b "$filepath")

current_date=$(date +"%d/%m/%Y")
author=$(whoami)  # Remplacez par votre nom

header=$(cat <<EOF

/*.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo. */
/*                                                                                      */
/*   Nom du fichier : $filename                                                            */
/*      Type du fichier : $filetype                                                    */
/*                                                                                      */
/*   By: $author                                                                             */
/*                                                                                      */
/*  Created: $current_date                                                                 */
/*  Updated: $current_date                                                                 */
/*                                                                                      */
/*.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo. */
EOF
)

echo "$header" | cat - "$filepath" > temp && mv temp "$filepath"