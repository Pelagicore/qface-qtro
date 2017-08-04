{% for module in system.modules %}
./bin/{{module|identifier}}_server &
{% endfor %}