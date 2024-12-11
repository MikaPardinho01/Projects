<?php
include_once './BancoDeDados.php';

// Recebe os dados JSON via POST
$data = json_decode(file_get_contents('php://input'));

// Verifica se há dados
if (! empty($data)) {
    // Conectar ao banco de dados
    $db = (new BancoDeDados())->iniciarConexao();

    $sql = "DELETE from produto WHERE id_externo = ?";
    $stmt = $db->prepare($sql);
    $stmt->execute([
        $data->id_externo,
    ]);
}
