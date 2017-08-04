{% for module in system.modules %}
killall {{module|identifier}}_server
{% endfor %}