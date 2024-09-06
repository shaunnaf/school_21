CREATE SEQUENCE seq_person_discounts
START WITH 1
INCREMENT BY 1;

DO $$
DECLARE
    current_row_count INTEGER;
BEGIN
    SELECT COUNT(*) INTO current_row_count FROM person_discounts;

    PERFORM setval('seq_person_discounts', current_row_count + 1);
END $$;

ALTER TABLE person_discounts
ALTER COLUMN id SET DEFAULT nextval('seq_person_discounts');

