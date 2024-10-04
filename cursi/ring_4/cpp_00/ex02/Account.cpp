#include <iostream>
#include <iomanip>
#include <ctime>
#include "Account.hpp"

# define COL_WIDTH 17

int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

int	Account::getNbAccounts( void ) {
	return (_nbAccounts);
}

int	Account::getTotalAmount( void ) {
	return (_totalAmount);
}

int	Account::getNbDeposits( void ) {
	return (_totalNbDeposits);
}

int	Account::getNbWithdrawals( void ) {
	return (_totalNbWithdrawals);
}

Account::Account( void )
	: _accountIndex(0), _amount(0), _nbDeposits(0), _nbWithdrawals(0) {
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";"
				<< "amount:" << _amount << ";"
				<< "created" << std::endl;
	_nbAccounts++;
}

Account::Account( int initial_deposit ) : _accountIndex(_nbAccounts),
		_amount(initial_deposit), _nbDeposits(0), _nbWithdrawals(0) {
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";"
			  << "amount:" << _amount << ";"
			  << "created" << std::endl;
	_nbAccounts++;
	_totalAmount += initial_deposit;
}

Account::~Account( void ) {
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";"
			  << "amount:" << _amount << ";"
			  << "closed" << std::endl;
	_nbAccounts--;
}

void	Account::displayAccountsInfos( void ) {
	_displayTimestamp();
	std::cout << "accounts:" << _nbAccounts  << ";";
	std::cout << "total:" << _totalAmount  << ";";
	std::cout << "deposits:" << _totalNbDeposits  << ";";
	std::cout << "withdrawals:" << _totalNbWithdrawals;
    std::cout << std::endl;
}

void	Account::makeDeposit( int deposit ) {
	_displayTimestamp();
	std::cout << "index:" << _accountIndex  << ";";
	std::cout << "p_amount:" << _amount  << ";";
	std::cout << "deposit:" << deposit  << ";";
	_amount += deposit;
	std::cout << "amount:" << _amount  << ";";
	_nbDeposits++;
	std::cout << "nb_deposits:" << _nbDeposits;
    std::cout << std::endl;
	_totalAmount += deposit;
	_totalNbDeposits++;
}

bool	Account::makeWithdrawal( int withdrawal ) {
	_displayTimestamp();
	std::cout << "index:" << _accountIndex  << ";";
	std::cout << "p_amount:" << _amount  << ";";
	if (_amount < withdrawal) {
		std::cout << "withdrawal:refused" << std::endl;
		return (false);
	}
	std::cout << "withdrawal:" << withdrawal  << ";";
	_amount -= withdrawal;
	std::cout << "amount:" << _amount  << ";";
	_nbWithdrawals++;
	std::cout << "nb_withdrawals:" << _nbWithdrawals;
    std::cout << std::endl;
	_totalAmount -= withdrawal;
	_totalNbWithdrawals++;
	return (true);
}

int		Account::checkAmount( void ) const {
	return (0);
}

void	Account::displayStatus( void ) const {
	_displayTimestamp();
	std::cout << "index:" << _accountIndex  << ";";
	std::cout << "amount:" << _amount  << ";";
	std::cout << "deposits:" << _nbDeposits  << ";";
	std::cout << "withdrawals:" << _nbWithdrawals;
    std::cout << std::endl;
}

void Account::_displayTimestamp(void) {
	std::time_t now = std::time(0);
	std::tm *tm_now = std::localtime(&now);

	std::cout << "[" 
			  << (tm_now->tm_year + 1900)
			  << std::setw(2) << std::setfill('0') << (tm_now->tm_mon + 1)
			  << std::setw(2) << std::setfill('0') << tm_now->tm_mday
			  << "_" 
			  << std::setw(2) << std::setfill('0') << tm_now->tm_hour
			  << std::setw(2) << std::setfill('0') << tm_now->tm_min
			  << std::setw(2) << std::setfill('0') << tm_now->tm_sec
			  << "] ";
}
