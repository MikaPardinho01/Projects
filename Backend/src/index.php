<?php

include_once './BancoDeDados.php';

if (isset($_GET) && isset($_GET['listar'])) {
    $query = "SELECT * FROM produto LIMIT 0, 5";

    $teste = new BancoDeDados;

    var_dump($teste);
}

echo 'Ola Mundo';