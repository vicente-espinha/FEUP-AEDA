## AEDA_FEUP
A Place in the Sun

# Parte 1

A empresa "A place in the Sun" é dedicada à realização de reservas para alojamento em hóteis, apart-hóteis, bed-n-breakfast, flats, e quartos em shared-houses. Sem ser proprietária de quaisquer dos alojamentos, a empresa funciona como um brocker para quem desejar disponibilizar quartos, flats e apartamentos para aluguer.

A empresa terá, portanto, uma carteira de fornecedores e de clientes registados; porém, poderá haver clientes ocasionais, que realizam reservas esporadicamente. Quando um fornecedor se regista no sistema, deve incluir os seus dados (nome, NIF, morada), e a lista de ofertas que deseja disponibilizar, com as respetivas características.

As ofertas de alojamento poderão ser de vários tipos, nomeadamente: quartos (quarto simples, quarto duplo, quarto duplo com uma cama adicional, quarto triplo, quarto) em hotel, casa partilhada (shared-house), ou bed-n-breakfast; flat (com um quarto, cozinha e casa de banho); apartamento (com um ou mais quartos, possivelmente suite, cozinha, e sala de estar). Os valores de cada hospedagem são definidos em função do número de noites, semanas ou meses, de acordo com a definição do fornecedor. O fornecedor também deve definir as datas em que o serviço poderá estar indisponível.

Para realizar uma reserva, o utilizador deverá antes poder fazer uma consulta das ofertas em uma determinada localidade (cidade), para as datas pretendidas; tendo encontrado uma oferta do seu agrado, poderá realizar uma reserva, passando a oferta a estar indisponível para as datas da reserva. Para os clientes registados, a empresa pretende implementar um sistema de pontos, em função da sua utilização do sistema. Os clientes não registados não conseguem acumular pontos. Os fornecedores registados na empresa deverão pagar uma taxa de serviço, por cada alojamento efetivamente confirmado, cujo valor dependerá do tipo de alojamento (quartos, flats, apartamentos). Cancelamentos de reserva são possíveis, mas poderão incorrer em taxas administrativas; ao efetuar um cancelamento, o cliente receberá 100% do valor pago, se realizado com antecedência de um mês da data de início de reserva; se cancelar até 15 dias antes do início da reserva receberá 50% do valor. Se for realizado após estes prazos, não haverá lugar a reembolso. 

#Parte 2 

Complete o sistema já implementado com as seguintes funcionalidades:

* Para efeitos de auditoria, a empresa precisa guardar o histórico das reservas realizadas. As faturas das reservas executadas são então guardadas numa Árvore Binária de Pesquisa, ordenadas alfabeticamente pelo nome do cliente; para clientes com histórico de muitas reservas, estas são ordenadas a partir das mais antigas, até às mais recentes.

* A fim de manter o interesse das unidades habitacionais pelos clientes sempre em alta, a empresa decide implementar um sistema de ofertas para as unidades que são reservadas há mias de um determinado tempo. Para este efeito, guarda numa Fila de Prioridade, por ordem decrescente do período de tempo desde o último aluguer, estas tais unidades(quartos, flats, etc.), a fim de priorizar descontos para aquelas que não são alugadas há muito tempo. Os maiores descontos serão dados às unidades que não são alugadas há mais tempo.

* A empresa guarda numa Tabela de Dispersão os clientes inativos, que não realizam reservas há mais de um determinado tempo, para efeitos de envio de publicidade para as suas moradas. Sempre que um cliente inativo realiza uma nova reserva, ele volta a ser considerado um cliente ativo, regressando à carteira de clientes da empresa. Muitas vezes, a empresa realiza ações de atualização das moradas dos clientes inativos, a fim de manter a informação sempre correta das respetivas moradas.

