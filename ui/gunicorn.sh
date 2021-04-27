#!/bin/sh
gunicorn --chdir app app:app -w 16 --threads 4 -b ui:443