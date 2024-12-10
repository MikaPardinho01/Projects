<?php

include_once './BancoDeDados.php';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $uid = $_POST['uid'];

    if (!empty($uid)) {
        $db = new BancoDeDados();
        $conexao = $db->iniciarConexao();

        $query = "INSERT INTO produto (uid) VALUES (:uid)";
        $stmt = $conexao->prepare($query);
        $stmt->bindParam(':uid', $uid);

        if ($stmt->execute()) {
            echo json_encode(['success' => true, 'message' => 'UID salvo com sucesso.']);
        } else {
            echo json_encode(['success' => false, 'message' => 'Erro ao salvar o UID.']);
        }
    } else {
        echo json_encode(['success' => false, 'message' => 'UID não pode estar vazio.']);
    }
} else {
    echo json_encode(['success' => false, 'message' => 'Método não permitido.']);
}