<?php

include_once './config.php';

class BancoDeDados
{
    private $conexao;

    public function __construct()
    {
        $this->iniciarConexao(); 
    }

    public function iniciarConexao()
    {
        try {
            $this->conexao = new \PDO(sprintf(
                'mysql:host=%s;dbname=%s', DB_HOST, DB_DATABASE
            ), DB_USER, DB_PASSWORD);
        } catch (\PDOException $e) {
            var_dump('Erro ao conectar no banco de dados');
        }

        return $this->conexao;
    }
}