<?php

include_once './BancoDeDados.php';

if (isset($_GET) && isset($_GET['listar'])) {
    var_dump('Estou listando');
}