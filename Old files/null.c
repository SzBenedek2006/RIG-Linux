// Latest stuff... first 3 time incorrect
    if (total <= needAveraging) {
        if (*time1 && *time2 != 0) {
            if (*tCounter == 1) {
                *(&eta) = (total - progress) * ((*time1) - (*time2));
            } else {
                *(&eta) = (total - progress) * ((*time2) - (*time1));
            }
        }
    } else if (counter == 0) {
        if (*time1 && *time2 != 0) {
            if (*tCounter == 1) {
                *(&eta0) = (total - progress) * ((*time1) - (*time2));
            } else {
                *(&eta0) = (total - progress) * ((*time2) - (*time1));
            }
            *(&eta) = *(&eta0); // average calc
        }
    } else if (counter == 1) {
        if (*time1 && *time2 != 0) {
            if (*tCounter == 1) {
                *(&eta1) = (total - progress) * ((*time1) - (*time2));
            } else {
                *(&eta1) = (total - progress) * ((*time2) - (*time1));
            }
            *(&eta) = (*(&eta0) + *(&eta1)) / 2; // average calc
        }
    } else if (counter == 2) {
        if (*time1 && *time2 != 0) {
            if (*tCounter == 1) {
                *(&eta2) = (total - progress) * ((*time1) - (*time2));
            } else {
                *(&eta2) = (total - progress) * ((*time2) - (*time1));
            }
            *(&eta) = (*(&eta0) + *(&eta1) + *(&eta2)) / 3; // average calc
        }
    } else if (counter == 3) {
        if (*time1 && *time2 != 0) {
            if (*tCounter == 1) {
                *(&eta3) = (total - progress) * ((*time1) - (*time2));
            } else {
                *(&eta3) = (total - progress) * ((*time2) - (*time1));
            }
            *(&eta) = (*(&eta0) + *(&eta1) + *(&eta2) + *(&eta3)) / 4; // average calc
        }
    } else if (counter == 4) {
        if (*time1 && *time2 != 0) {
            if (*tCounter == 1) {
                *(&eta4) = (total - progress) * ((*time1) - (*time2));
            } else {
                *(&eta4) = (total - progress) * ((*time2) - (*time1));
            }
            *(&eta) = *(&eta0); // average calc
        }
    } else if (counter == 5) {
        if (*time1 && *time2 != 0) {
            if (*tCounter == 1) {
                *(&eta5) = (total - progress) * ((*time1) - (*time2));
            } else {
                *(&eta5) = (total - progress) * ((*time2) - (*time1));
            }
            *(&eta) = (*(&eta0) + *(&eta1)) / 2; // average calc
        }
    } else if (counter == 6) {
        if (*time1 && *time2 != 0) {
            if (*tCounter == 1) {
                *(&eta6) = (total - progress) * ((*time1) - (*time2));
            } else {
                *(&eta6) = (total - progress) * ((*time2) - (*time1));
            }
            *(&eta) = (*(&eta0) + *(&eta1) + *(&eta2)) / 3; // average calc
        }
    } else if (counter == 7) {
        if (*time1 && *time2 != 0) {
            if (*tCounter == 1) {
                *(&eta7) = (total - progress) * ((*time1) - (*time2));
            } else {
                *(&eta7) = (total - progress) * ((*time2) - (*time1));
            }
            *(&eta) = (*(&eta0) + *(&eta1) + *(&eta2) + *(&eta3)) / 4; // average calc
        }
    }
