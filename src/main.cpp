#include <modm/board.hpp>

extern "C" {
#include <daqp/src/daqp/api.h>
}

using namespace Board;

int
main()
{
	Board::initialize();
	Leds::setOutput();

	// Use the logging streams to print some messages.
	// Change MODM_LOG_LEVEL above to enable or disable these messages
	MODM_LOG_DEBUG   << "debug"   << modm::endl;
	MODM_LOG_INFO    << "info"    << modm::endl;
	MODM_LOG_WARNING << "warning" << modm::endl;
	MODM_LOG_ERROR   << "error"   << modm::endl;

	uint32_t counter(0);

	while (true)
	{
		Leds::write(1 << (counter % (Leds::width+1) ));
		modm::delay(500ms);

		MODM_LOG_INFO << "loop: " << counter++ << modm::endl;

        int n = 2; // Number of decision variables
        int m = 4; // Number of constraints (general + simple)
        int ms= 2; // Number of simple bounds
        double H[4] = {1, 0, 0, 1};
        double f[2] = {1,1}; 
        double A[4] = {1, 1, 1, -1};
        double bupper[4] = {1, 2, 3, 4};
        double blower[4] = {-1, -2, -3, -4};
        int sense[4] = {0,0,0,0}; 
        int *bin_ids = NULL; int nbin = 0; // No binary constraints


        DAQPProblem qp = {n,m,ms,H,f,A,bupper,blower,sense,bin_ids,nbin};
        double x[2],lam[4];
        DAQPResult result;
        result.x = x; // primal variable
        result.lam = lam; // dual variable
        daqp_quadprog(&result,&qp,NULL);

        MODM_LOG_INFO << "DAQP result is \n\t x= [" << x[0] << ", " << x[1] << " ]" << modm::endl;
        MODM_LOG_INFO << "\texitflag = " << result.exitflag << modm::endl;
        MODM_LOG_INFO << "\tsetup_time = " << result.setup_time << modm::endl;
        MODM_LOG_INFO << "\tsolve_time = " << result.solve_time << modm::endl;
        MODM_LOG_INFO << "\titer = " << result.iter << modm::endl;
	}

	return 0;
}