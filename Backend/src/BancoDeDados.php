<?php

// Inclui o arquivo de configuração com os detalhes da conexão ao banco de dados
include_once './config.php';

class BancoDeDados
{
    // Atributo privado para armazenar a conexão com o banco de dados
    private $conexao;

    /**
     * Método para iniciar a conexão com o banco de dados.
     * Usa PDO para estabelecer a conexão utilizando os dados de configuração.
     *
     * @return PDO|null Retorna a conexão PDO em caso de sucesso ou null em caso de falha.
     */
    public function iniciarConexao(): ?PDO
    {
        try {
            // Cria a conexão com o banco utilizando os dados de configuração
            $this->conexao = new \PDO(
                sprintf(
                    'mysql:host=%s;dbname=%s', // Formato do DSN para conexão MySQL
                    DB_HOST,                   // Host do banco de dados
                    DB_DATABASE                // Nome do banco de dados
                ),
                DB_USER,                     // Usuário do banco
                DB_PASSWORD                  // Senha do banco
            );
        } catch (\PDOException $e) {
            // Exibe uma mensagem de erro caso a conexão falhe
            var_dump('Erro ao conectar no banco de dados: ' . $e->getMessage());
        }

        // Retorna a conexão (pode ser usada por outros métodos)
        return $this->conexao;
    }
}
